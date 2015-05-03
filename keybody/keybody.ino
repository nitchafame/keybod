
/* ---------------------------
---------------------------
     Project Body Keyboard 
     code by Nitcha Fame Tothong x firmread
     ---------------------------
--------------------------- */ 

#include "Wire.h"
#include "CapPin.h"
#include "Adafruit_MPR121.h"
#include "Adafruit_NeoPixel.h"
#include "avr/power.h"


/* -----------
    MPU-6050 Accel + Gyro
----------- */ 
const int MPU = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;


/* -----------
    Leaning Logics
----------- */ 
int delayval = 500;
int leanCount = 0;
boolean bDidType = false;


/* -----------
    CapPin
----------- */ 
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

// sensitivity threshold
#define THRESH 500
float smoothed[8] = {0, 0, 0, 0, 0, 0, 0, 0};


/* -----------
    MPR121 Capacitive Breakouts
----------- */  
// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;


/* -----------
    NeoPixels 
----------- */ 
#define NUMPIXELS      1
#define PIN            4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);





// ------------------------------------------------------------------

void setup() {
  while (!Serial); 
  Serial.begin(115200);
  setupAccel();
  setupCap();
  Keyboard.begin(); // initializes the Keyboard lib
  pixels.begin(); // initializes the NeoPixel lib
}

// ------------------------------------------------------------------

void loop() {

  readAccel();
  printAccel();
  
  
  // lean in
  if (AcX > 10000) {
    // haven't count/got notice
    if (!bDidType) {
      leanCount++;
     
      // led notice
      pixels.setPixelColor(0, pixels.Color(150, 0, 0)); // Moderately bright red color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
      
      // keyboard out notice
      Keyboard.print("You just leaned ");
      Keyboard.print(leanCount);
      Keyboard.println(" times.");
      
      bDidType = true;
    }
  }
  // lean out
  else {
    bDidType = false;
    // TODO: some feedback loops here
    //      Keyboard.println("Good");
  }
  
  // led start after 3 leans
  if (leanCount > 3) {
    pixels.setPixelColor(0, pixels.Color(150, 150, 150)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  } else {

  }
  
  keyboardCapPin();
  
  
  
  printCap();
  //printCapDebug();
  printCap();
}



