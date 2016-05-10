#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;
float x_acc, gyro;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(1200);
	Serial.println("Initialize MPU");
	mpu.initialize();
}

void loop(){
	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	Serial.print("ax= ");
	Serial.print(ax);
	Serial.print("\t\t");
	Serial.print("gy= ");
	Serial.print(gy);
	Serial.print("\t\t");
	
	x_acc= (ax - (-74))*(2);
	Serial.print("x_acc= "); Serial.print(x_acc);
	Serial.print("\t\t");
	
	gyro= (gy - (-181))*(500);
	Serial.print("gyro= ");
	Serial.print(gyro);
	Serial.print("\n");
}