
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#if not defined (_VARIANT_ARDUINO_DUE_X_)
	#include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE 0
#define MINIMUM_FIRMWARE_VERSION "0.6.6"

Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);


// accel stuffs
// I2C address of the MPU-6050
const int MPU = 0x68;
//int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int8_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
boolean bDidType = false;


// A small error handling helper
void error(const __FlashStringHelper*err) {
	Serial.println(err);
	while (1);
}


/*
 error handling syntax note:
 this set of code call rename function and return if error happens
 
 // print to serial so we know what's going on
 Serial.println(F(""));
 
 // send command via BLE and run error fn if it's return failure feedback
 if (!ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Bluefruit clickKick" )) )
	error(F("Could not set device name?"));
 
 */

void setup(void) {
	
	// required for Flora & Micro
	while (!Serial);
	delay(500);
	
	// for accel
	Wire.begin();
	Wire.beginTransmission(MPU);
	Wire.write(0x6B);  // PWR_MGMT_1 register
	Wire.write(0);     // set to zero (wakes up the MPU-6050)
	Wire.endTransmission(true);
	
	
	// HID mouse
	Serial.begin(115200);
	Serial.println(F("ClickKick - Bluefruit HID Mouse"));
	Serial.println(F("---------------------------------------"));
	
	/* Initialise the module */
	Serial.print(F("Initializing the Bluefruit LE module: "));
	if ( !ble.begin(VERBOSE_MODE) )
		error(F("Couldn't find Bluefruit, check command mode & wiring"));
	
	Serial.println( F("OK!") );
	
	// not running as variable above set to 0
	if ( FACTORYRESET_ENABLE ) {
		Serial.println(F("Performing a factory reset: "));
		if ( ! ble.factoryReset() )
			error(F("Couldn't factory reset"));
	}
	
	// Disable command echo from Bluefruit
	ble.echo(false);
	
	// Print Bluefruit information
	Serial.println("Requesting Bluefruit info:");
	ble.info();
	
	// Change the device name to make it easier to find
	Serial.println(F("Setting device name to 'Bluefruit clickKick': "));
	if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Bluefruit clickKick" )) )
		error(F("Could not set device name?"));
	
	// This demo only available for firmware from 0.6.6
	if ( !ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
		error(F("Requires firmware version " MINIMUM_FIRMWARE_VERSION " or higher!"));
	
	// Enable HID Service (including Mouse)
	Serial.println(F("Enable HID Service (including Mouse): "));
	if (! ble.sendCommandCheckOK(F( "AT+BleHIDEn=On"  )))
		error(F("Failed to enable HID (firmware >=0.6.6?)"));
	
	// Add or remove service requires a reset
	Serial.println(F("Performing a SW reset (service changes require a reset): "));
	if (! ble.reset() )
		error(F("Could not reset??"));
	
	Serial.println();
}

void loop(void) {
	
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
	
	Serial.print(" | AcX = "); Serial.print(AcX);
	Serial.print(" | AcY = "); Serial.print(AcY);
	Serial.print(" | AcZ = "); Serial.print(AcZ);
	//equation for temperature in degrees C from datasheet
	Serial.print(" | Tmp = "); Serial.print(Tmp / 340.00 + 36.53);
	Serial.print(" | GyX = "); Serial.print(GyX);
	Serial.print(" | GyY = "); Serial.print(GyY);
	Serial.print(" | GyZ = "); Serial.println(GyZ);
	
	
	/* 
	 
	 Mouse Action BLE Services for Command mode
	 https://learn.adafruit.com/introducing-adafruit-ble-bluetooth-low-energy-friend/ble-services#at-plus-blehidmousemove
	
	 */
	
	
	
	// Press (and hold) the Left mouse's button
	if ( ble.sendCommandCheckOK(F("AT+BleHidMouseButton=L,press")) ) {
		// delay a bit
		delay(250);
		
		// Mouse moves according to the user's input
		// Parameter: X Ticks (+/-), Y Ticks (+/-), Scroll Wheel (+/-), Pan Wheel (+/-)
		
		//Right
		if (AcY > 0) {
			ble.print(F("AT+BleHidMouseMove= 2,,,"));
		}
		
		if ( ble.waitForOK() ) Serial.println( F("OK!") );
		else Serial.println( F("FAILED!") );
		
		// Release the Left mouse's button
		// ble.sendCommandCheckOK(F("AT+BleHidMouseButton=0"));
	}
	
	else {
		// Failed, probably pairing is not complete yet
		Serial.println( F("Please make sure Bluefruit is paired and try again") );
	}
}
