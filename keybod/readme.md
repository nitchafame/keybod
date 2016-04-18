# keybod
### dependencies:  
* Simple Capacitive Sensing for Arduino https://github.com/moderndevice/CapSense
* MPR121-based capacitive sensors https://github.com/adafruit/Adafruit_MPR121_Library
* Adafruit NeoPixel library https://github.com/adafruit/Adafruit_NeoPixel

### references:  
* Adafruit's Plush Game Controller tutorial
	* https://learn.adafruit.com/plush-game-controller/the-code
	* https://github.com/adafruit/adafruit_flora_game_controller
* MPR121 tutorial https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/wiring
	* **To hook up multiple MPR121** 
		* ADDR is the I2C address select pin. By default this is pulled down to ground with a 100K resistor, for an I2C address of 0x5A. You can also connect it to the 3Vo pin for an address of 0x5B, the SDA pin for 0x5C or SCL for address 0x5D 
* MPU-6050 Short example sketch http://playground.arduino.cc/Main/MPU-6050#short
* MPU-6050 i2c libs **not using just for ref** https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
