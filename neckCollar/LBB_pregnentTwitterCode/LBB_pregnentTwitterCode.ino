/*
  Author:  Eric Tsai
  Date:  December 29, 2015
  Light Blue Bean program to read Target brand digital pregnancy test
  Reference:
  http://legacy.punchthrough.com/bean/the-arduino-reference/sleep/
  http://legacy.punchthrough.com/bean/attachpinchangeinterrupt/
  http://legacy.punchthrough.com/bean/the-arduino-reference/detachpinchangeinterrupt/
  https://github.com/PunchThrough/PinChangeInt/blob/master/PinChangeInt.h
*/

#include <PinChangeInt.h>
#define MAX_BEAN_SLEEP 4294967295



//define pins
static uint8_t pinClock = 0;  //pin for LCD clock
static uint8_t pinNot = 1;    //pin for "Not" text
static uint8_t pinPreg = 2;   //pin for "Pregnant" text

uint8_t state;
static uint8_t state_sleep = 0;   //wait for wakeup pin (LCD clock)
static uint8_t state_testing = 1; //wait for test results
static uint8_t state_result = 2;  //transmit results
static uint8_t state_idle = 3;    //wait for disconnect


uint8_t valClock;
uint8_t valPreg;
uint8_t valNot;

int counter_preg = 0;
int counter_not = 0;
bool flag_preg = 0;
bool flag_not = 0;

//adjust these parameters to conclude test faster
static uint8_t lcd_pos_count = 2;
static unsigned long lcd_pos_timer = 1000;

//timers
unsigned long timer_read_acc = 0;   //interval for reading accelerometer
unsigned long timer_pinClock = 0;   //used to check if still hooked up

unsigned long timer_display_preg = 0;
unsigned long timer_display_not = 0;


//led max intensity
static uint8_t red = 255;
static uint8_t green = 255;
static uint8_t blue = 255;

uint8_t testing_led_intensity;      //LED intensity while state_testing
unsigned long timer_testing_blue;
int flag_led_increase = 1;

bool isConnected = 0;

//acceleration
int16_t y_raw = 0;
AccelerationReading accel = {0, 0, 0};


//vars for serial input
char buffer[10];
char buffer2[10];
size_t length = 10;



void setup()
{
  pinMode(pinClock, INPUT);
  pinMode(pinPreg, INPUT);
  pinMode(pinNot, INPUT);

  state = state_sleep;
}


void wakeup_routine()
{
  //do nothing
}

void loop()
{
  if (state == state_sleep){
    //reset variables ready for next test
    Bean.setLed(0, 0, 0);
    counter_preg = 0;
    counter_not = 0;
    flag_preg = 0;
    flag_not = 0;

    //attach interrupt before sleep, detach interrupt after wake
    attachPinChangeInterrupt(0, wakeup_routine, CHANGE);
    Bean.sleep(MAX_BEAN_SLEEP);

    //upon wake up, assume in test mode
    detachPinChangeInterrupt(0);
    state = state_testing;

    timer_pinClock = millis();

    //handy visual indication of bluetooth connectivity to Raspberry Pi
    isConnected = Bean.getConnectionState();
    if (isConnected)
    {
      Bean.setLed(0, green, 0);
    }
    else
    {
      Bean.setLed(red, 0, 0);
    }
    delay(1000);
    Bean.setLed(0, 0, 0);
    timer_testing_blue = millis();
    flag_led_increase = 1;
    testing_led_intensity = 0;

    timer_read_acc = millis();
  } //end if state_sleep



  //read the three pin values
  valClock = digitalRead(pinClock);
  valPreg = digitalRead(pinPreg);
  valNot = digitalRead(pinNot);

  //time how long ago module may be disconnected
  if (valClock == 1) { //if 0 for too long (meaning module disconnected), go back to sleep
    timer_pinClock = millis();
  }
  else{
    if ((millis() - timer_pinClock) > 8000){  //sleep after 8 seconds disconnected
      state = state_sleep;
    }
  }


  //---------------------------------------------
  if (state == state_testing)
  {
    if (valClock != valNot) { //"Not" is being displayed
      if (counter_not < 7) {
        counter_not++;
      }
    }
    else {  //"Not" isn't being displayed
      if (counter_not > -7){
        counter_not--;
      }
      if (counter_not < -2){
        timer_display_not = millis();
      }
    }


    if (valClock != valPreg) { //"Pregnant" is being displayed
      if (counter_preg < 7){ 
        counter_preg++;
      }
    }
    else {  //"Prenant" not being displayed
      if (counter_preg > -7){
        counter_preg--;
      }
      if (counter_preg < -2) {
        timer_display_preg = millis();
      }
    }

    //watch accelerometer
    if ((millis() - timer_read_acc) > 3000){   //read accelerometer every 3 seconds
      timer_read_acc = millis();
      accel = Bean.getAcceleration();
      y_raw = accel.yAxis;
    }

    //transition state
    if ((counter_preg > lcd_pos_count) || (counter_not > lcd_pos_count)){
      unsigned long current_time = millis();
      if (( (current_time - timer_display_preg) > lcd_pos_timer) || ((current_time - timer_display_not) > lcd_pos_timer)){

        if (counter_preg > 0){
          flag_preg = 1;
        }
        else{
          flag_preg = 0;
        }

        if (counter_not > 0){
          flag_not = 1;
        }
        else{
          flag_not = 0;
        }
        state = state_result;
      }
    } //end if transition


    //B, BL, BLU, BLUE
    if ((millis() - timer_testing_blue) > 100) {   //update LED ~10Hz.  Random
    
      timer_testing_blue = millis();
      if (flag_led_increase == 1){
        testing_led_intensity = testing_led_intensity + 20;
      }
      else{
        testing_led_intensity = testing_led_intensity - 20;
      }

      //Bean.setLed(0, 0, testing_led_intensity);   //blue

      if (y_raw > -210){
        Bean.setLed(0, 0, testing_led_intensity);   //blue
      }
      else  //upside down, solid blue
        Bean.setLed(0, 0, blue);

      //flip bright to dim
      if ((testing_led_intensity > 230) && (flag_led_increase == 1)){
        flag_led_increase = 0;
        //Serial.println("flip 0");
      }
      else if ((testing_led_intensity < 20) && (flag_led_increase == 0)){
        flag_led_increase = 1;
        //Serial.println("flip 1");
      }
    }

    //less than 3ms to execute loop.  At 40Hz LCD frequency, we get 25ms period.
    delay(7);


  } // end if state_testing



  if (state == state_result){
    uint8_t blink_red = 0;
    uint8_t blink_green = 0;
    uint8_t blink_blue = 0;

    //transmit results
    if ( (flag_preg) & (flag_not) ) { //not pregnant
      Serial.println("11"); //arbitrary code for not pregnant
      blink_red = 255;
      blink_green = 0;
    }

    else if ((flag_preg) & (!flag_not)) { //pregnant
      Serial.println("12"); //arbitrary code for pregnant
      blink_red = 0;
      blink_green = 255;
    }
    else { //not possible
      Serial.println("20"); //arbitrary code for error
      blink_red = 255;
      blink_green = 255;
      blink_blue = 255;
    }

    //Bean.setLed(red, green, blue);
    Bean.setLed(blink_red, blink_green, blink_blue);
    delay(500);
    Bean.setLed(0, 0, 0);
    delay(500);
    Bean.setLed(blink_red, blink_green, blink_blue);
    delay(500);
    Bean.setLed(0, 0, 0);
    delay(500);
    Bean.setLed(blink_red, blink_green, blink_blue);  //light stays on

    state = state_idle;  //transition
  } //end state_result
} //end loop


