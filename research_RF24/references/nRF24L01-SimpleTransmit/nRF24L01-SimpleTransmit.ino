/* YourDuinoStarter Example: Simple nRF24L01 Transmit
  - WHAT IT DOES: Transmits simple fixed data with nRF24L01 radio
  - SEE the comments after "//" on each line below
   Start with radios about 4 feet apart.
  - SEE the comments after "//" on each line below
  - CONNECTIONS: nRF24L01 Modules See:
  http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
  Uses the RF24 Library by TMRH2o here:
  https://github.com/TMRh20/RF24
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 7
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
*/

#include <SPI.h>
#include "RF24.h"
RF24 myRadio (7, 8); 
byte addresses[][6] = {"1Node"}; // Create address for 1 pipe.
int dataTransmitted;

void setup(){
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("RF24/Simple Transmit data Test"));
  Serial.println(F("Questions: terry@yourduino.com"));
  dataTransmitted = 100; // Arbitrary known data to transmit. Change it to test...
  myRadio.begin();
  myRadio.setChannel(108);  // Above most Wifi Channels
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  myRadio.setPALevel(RF24_PA_MIN);
  //  myRadio.setPALevel(RF24_PA_MAX);  // Uncomment for more power

  myRadio.openWritingPipe( addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  delay(1000);
}


void loop(){
  myRadio.write( &dataTransmitted, sizeof(dataTransmitted) );

  Serial.print(F("Data Transmitted = "));
  Serial.print(dataTransmitted);
  Serial.println(F(" No Acknowledge expected"));
  dataTransmitted = dataTransmitted + 1;
  delay(500);

}
