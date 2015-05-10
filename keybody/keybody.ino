#include <Adafruit_NeoPixel.h>


/* ---------------------------
---------------------------
     Project Body Keyboard 
     code by nitchafame x firmread
     ---------------------------
--------------------------- */ 

#include "Wire.h"
//#include "CapPin.h"
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
//CapPin cPin_4 = CapPin(4);    // read pin 4 - connect to
//CapPin cPin_5 = CapPin(5);     // read pin 5 - connect to A
//CapPin cPin_6 = CapPin(6);     // read pin 6 - connect to
//CapPin cPin_8 = CapPin(8);    // read pin 8 - connect to D
//CapPin cPin_9 = CapPin(9);     // read pin 9 - connect to
//CapPin cPin_10  = CapPin(10);     // read pin 10 - connect to S
//CapPin cPin_11  = CapPin(11);     // read pin 11 - connect to *******
//CapPin cPin_12  = CapPin(12);     // read pin 12 - connect to Backspace
//
//CapPin pins[] = {cPin_4, cPin_5, cPin_6, cPin_8, cPin_9, cPin_10, cPin_11, cPin_12};
//
//// WASD D-pad, select = Return, start = Space, LeftButton = z, RightButton = x
//char Keys[] =   {'x', 'a', ' ', 'd', 'w', 's', KEY_RETURN, KEY_BACKSPACE};
//boolean currentPressed[] = {false, false, false, false, false, false, false, false};
//
//// sensitivity threshold
//#define THRESH 500
//float smoothed[8] = {0, 0, 0, 0, 0, 0, 0, 0};


/* -----------
    MPR121 Capacitive Breakouts
----------- */  
// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Adafruit_MPR121 cap3 = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;
uint16_t lasttouched3 = 0;
uint16_t currtouched3 = 0;


/* -----------
    NeoPixels 
----------- */ 
#define NUMPIXELS      1
#define PIN            13
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int ledMode = 0;


/* -----------
    Vibe Motor 
----------- */ 
int vibePin = 6;
int vibeVal = 0;
int vibeMode = 0;



// ------------------------------------------------------------------

void setup() {
  pixels.begin(); // initializes the NeoPixel lib
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); 
  pixels.show();
  while (!Serial); 
  Serial.begin(115200);
  Serial.println("started");
  setupAccel();
  Serial.println("setup accel done");
  setupCap();
  setupCap2();
  setupCap3();
  Serial.println("setup cap done");
  
  pinMode(vibePin, OUTPUT);
  Keyboard.begin(); // initializes the Keyboard lib
}

// ------------------------------------------------------------------

void loop() {

  readAccel();
//  printAccel();
  
//  leanEvent();

  
  ledUpdate();
  vibeUpdate();
  //keyboardCapPin();
  
  keyInputCap();
  keyInputCap2();
  keyInputCap3();
  //printCapDebug();
}



