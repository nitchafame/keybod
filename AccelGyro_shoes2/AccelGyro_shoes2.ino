// MPU-6050 Short Example Sketch
// By Arduino User JohnChi - August 17, 2014
// Edit by Nitcha Tothong

#include<Wire.h>
int counter = 0;
const int MPU = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

boolean bDidType = false;

const int xAxis = A1;         //analog sensor for X axis
const int yAxis = A2;         // analog sensor for Y axis

int range = 12;               // output range of X or Y movement
int responseDelay = 4;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value
int minima[] = {1023, 1023};  // actual analogRead minima for {x, y}
int maxima[] = {0, 0};        // actual analogRead maxima for {x, y}
int axis[] = {xAxis, yAxis};  // pin numbers for {x, y}
int mouseReading[2];          // final mouse readings for {x, y}

enum gesture {
  UP,
  R,
  DW,
  L,
  NONE
};

gesture comboCW [] = { UP, R, DW, L, UP, R };
int comboCWcounter = 0;

void setup() {

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  Mouse.begin();


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

  //  Serial.print(" | AcX = "); Serial.print(AcX);
  //  Serial.print(" | AcY = "); Serial.print(AcY);
  //  Serial.print(" | AcZ = "); Serial.print(AcZ);
  //  Serial.print(" | Tmp = "); Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
  //  Serial.print(" | GyX = "); Serial.print(GyX);
  //  Serial.print(" | GyY = "); Serial.print(GyY);
  //  Serial.print(" | GyZ = "); Serial.println(GyZ);

  gesture currGesture;

  if (AcX > 0 && AcX < 9000 && AcY > 2500 &&  AcY < 5000) {
    currGesture = UP;

  } else if (AcX > 4500 && AcX < 8000 && AcY > 1000 && AcY < 4500) {
    currGesture = R;

  } else if (AcX < -8000 && AcX > -14000 && AcY > 1000 && AcY < 5000) {
    currGesture = DW;

  } else if (AcX < -7000 && AcX > -17000 && AcY > 8000 && AcY < 15000) {
    currGesture = L;
    
  } else {
    currGesture = NONE;
  }
  Serial.print (currGesture);





  //mouseMove();

  //Serial.print(reading);

  //-----Actions - Click

  if (AcX > 10000) {
    if (!bDidType) {
      counter++;
      Mouse.click();
      Mouse.end();
      bDidType = true;
    }
  }
  else {
    bDidType = false;
    //      Keyboard.println("Good");
  }

  //-----Actions - Mouse Move

  bool up = AcX > 0 && AcX < 9000 && AcY > 2500 &&  AcY < 5000;
  bool r = AcX > 4500 && AcX < 8000 && AcY > 1000 && AcY < 4500;
  bool dw = AcX < -8000 && AcX > -14000 && AcY > 1000 && AcY < 5000;
  bool l = AcX < -7000 && AcX > -17000 && AcY > 8000 && AcY < 15000;

  int gestureR[] = { up, r, dw, l, up, r, dw};


  // Up
  if (up == true) {
    Mouse.move(0, -5, 0);
    // Serial.print("gestureR works!!"); //Serial.print(gestureOne);

  } else {
    Mouse.move(0, 5, 0);
  }


  //  // Right
  //  if (AcY < 15000 && AcY > 1500 ) {
  //    Mouse.move(20, 1, 3);
  //  }
  //
  //  // Down
  //  else if (AcX < 7000 && AcX > -2000 ) {
  //    Mouse.move(0, 15, 0);
  //  }
  //  // Left
  //  else if (AcY > -15000 && AcY < -1500 ) {
  //    Mouse.move(-20, 0, 0);
  //  }





  delay(103);
}

//----- Simple lowpass filter
// requires recycling the output in the "smoothedVal" param

//int smooth(int data, float filterVal, float smoothedVal) {
//
//  if (filterVal > 1) {     // check to make sure param's are within range
//    filterVal = .999999;
//  }
//  else if (filterVal <= 0) {
//    filterVal = 0;
//  }
//  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
//  return (int)smoothedVal;
//  delay(333);
//}
