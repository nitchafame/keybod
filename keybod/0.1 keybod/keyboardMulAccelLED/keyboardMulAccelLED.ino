
//----- Project Body Keyboard

#include <CapPin.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include "Adafruit_MPR121.h"


// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1
#define PIN            4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//const int buttonPin = 4;          // input pin for pushbutton
//int previousButtonState = HIGH;   // for checking the state of a pushButton
int delayval = 500; // delay for half a second
int counter = 0;                  // button push counter
const int MPU = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

CapPin cPin_4 = CapPin(4);    // read pin 4 - connect to
CapPin cPin_5 = CapPin(5);     // read pin 5 - connect to A
CapPin cPin_6 = CapPin(6);     // read pin 6 - connect to
CapPin cPin_8 = CapPin(8);    // read pin 8 - connect to D
CapPin cPin_9 = CapPin(9);     // read pin 9 - connect to
CapPin cPin_10  = CapPin(10);     // read pin 10 - connect to S
CapPin cPin_11  = CapPin(11);     // read pin 11 - connect to *******
CapPin cPin_12  = CapPin(12);     // read pin 12 - connect to Backspace

CapPin pins[] = {cPin_4, cPin_5, cPin_6, cPin_8, cPin_9, cPin_10, cPin_11, cPin_12};

// WASD D-pad, select = Return, start = Space, LeftButton = z, RightButton = x
char Keys[] =   {'x', 'a', ' ', 'd', 'w', 's', KEY_RETURN, KEY_BACKSPACE};
boolean currentPressed[] = {false, false, false, false, false, false, false, false};
boolean bDidType = false;

// sensitive or not sensitive enough
#define THRESH 500
float smoothed[8] = {0, 0, 0, 0, 0, 0, 0, 0};


//MPR121
// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  while (!Serial); 

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  //  pinMode(buttonPin, INPUT);
  //while (!Serial)
  Serial.begin(115200);
  
  
  //MPR121
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  
  
  
  Keyboard.begin();
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  //-----Notification Input from Sensor

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
   Serial.print(" | AcX = "); Serial.print(AcX);
   Serial.print(" | AcY = "); Serial.print(AcY);
   Serial.print(" | AcZ = "); Serial.print(AcZ);
   Serial.print(" | Tmp = "); Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
   Serial.print(" | GyX = "); Serial.print(GyX);
   Serial.print(" | GyY = "); Serial.print(GyY);
   Serial.print(" | GyZ = "); Serial.println(GyZ);

  for (int i = 0; i < 8; i++) {
    delay(1);
    long total1 = 0;
    long start = millis();
    long total =  pins[i].readPin(2000);
    //    int buttonState = digitalRead(buttonPin);

    if (counter > 3) {
      pixels.setPixelColor(0, pixels.Color(150, 150, 150)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
    } else {

    }
    if (AcX > 10000) {
      if (!bDidType) {
        counter++;
       
          pixels.setPixelColor(0, pixels.Color(150, 0, 0)); // Moderately bright red color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(delayval); // Delay for a period of time (in milliseconds).
        
        Keyboard.print("You just leaned ");
        Keyboard.print(counter);
        Keyboard.println(" times.");
        bDidType = true;
      }
    }
    else {
      bDidType = false;
      //      Keyboard.println("Good");
    }


    //-----Notification Input button

    //if the button state has changed,
    //    if ((buttonState != previousButtonState)
    //        // and it's currently pressed:
    //        && (buttonState == HIGH)) {
    //      counter++;
    //      Serial.print("counter : "); Serial.println(counter);
    //
    //      //-----Type out a message
    //      //Keyboard.press(0x82); //hexadecimal value for KEY_LEFT_ALT
    //      // Keyboard.press(SP);
    //      Keyboard.print("You just leaned ");
    //      Keyboard.print(counter);
    //      Keyboard.println(" times.");
    //
    //    } // save the current button state for comparison next time:
    //    previousButtonState = buttonState;


    //-----Capacitive sensing

    // check if we are sensing that a finger is touching && that it wasnt already pressed
    if ((total > THRESH) && (! currentPressed[i]) && (counter > 3)) {
      Serial.print("Key pressed #"); Serial.print(i);
      Serial.print(" ("); Serial.print(Keys[i]); Serial.println(")");
      currentPressed[i] = true;
      Keyboard.press(Keys[i]);
    }

    else if ((total <= THRESH) && (currentPressed[i])) {
      // key was released (no touch, and it was pressed before)
      Serial.print("Key released #"); Serial.print(i);
      Serial.print(" ("); Serial.print(Keys[i]); Serial.println(")");
      currentPressed[i] = false;
      Keyboard.release(Keys[i]);
    }
    delay(5);
  }
  
  
  
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}


//----- Simple lowpass filter

// requires recycling the output in the "smoothedVal" param
int smooth(int data, float filterVal, float smoothedVal) {

  if (filterVal > 1) {     // check to make sure param's are within range
    filterVal = .999999;
  }
  else if (filterVal <= 0) {
    filterVal = 0;
  }
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}
