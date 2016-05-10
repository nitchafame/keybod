
#include <Wire.h>

// accel stuffs
// I2C address of the MPU-6050
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
//int8_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
boolean bDidType = false;

float smAcX, smAcY, smAcZ, smTmp, smGyX, smGyY, smGyZ;
float smSpeed = 0.025;

void setup() {
  
  Serial.begin(115200);
  // for accel
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  
  smSpeed = constrain(smSpeed, 0, 0.999999);
}

void loop() {
  // put your main code here, to run repeatedly:

  // accel
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);
  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcX = Wire.read() << 8 | Wire.read();
  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcY = Wire.read() << 8 | Wire.read();
  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();
  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Tmp = Wire.read() << 8 | Wire.read();
  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyX = Wire.read() << 8 | Wire.read();
  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyY = Wire.read() << 8 | Wire.read();
  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();


  smAcX = smooth(AcX, smSpeed, smAcX);
  smAcY = smooth(AcY, smSpeed, smAcY);
  smAcZ = smooth(AcZ, smSpeed, smAcZ);
  smTmp = smooth(Tmp, smSpeed, smTmp);
  smGyX = smooth(GyX, smSpeed, smGyX);
  smGyY = smooth(GyY, smSpeed, smGyY);
  smGyZ = smooth(GyZ, smSpeed, smGyZ);
  
//
//  Serial.print(" | AcX = "); Serial.print(smAcX);
//  Serial.print(" | AcY = "); Serial.print(smAcY);
//  Serial.print(" | AcZ = "); Serial.print(smAcZ);
//  //equation for temperature in degrees C from datasheet
//  Serial.print(" | Tmp = "); Serial.print(smTmp / 340.00 + 36.53);
//  Serial.print(" | GyX = "); Serial.print(smGyX);
//  Serial.print(" | GyY = "); Serial.print(smGyY);
//  Serial.print(" | GyZ = "); Serial.println(smGyZ);

  // apply trigonometry to get the pitch and roll:
  float pitch = atan(smAcX/sqrt(pow(smAcY,2) + pow(smAcZ,2)));
  float roll = atan(smAcY/sqrt(pow(smAcX,2) + pow(smAcZ,2)));
  
  //convert radians into degrees
  pitch = pitch * (180.0/PI);
  roll = roll * (180.0/PI) ;

  Serial.print(pitch);
  Serial.print(",");
  Serial.println(roll);
}



//----- Simple lowpass filter
// requires recycling the output in the "smoothedVal" param

float smooth(int data, float filterVal, float smoothedVal) {
  smoothedVal = (smoothedVal * (1 - filterVal)) + (data  *  filterVal);
  return smoothedVal;
}
