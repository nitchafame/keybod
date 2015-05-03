void setLedMode(int mode){
  ledMode = mode;
}

void ledUpdate(){
  if (ledMode == 0){
    pixels.setPixelColor(0, pixels.Color(sinAnimateRange(20,255,1), 0, 0)); 
    pixels.show();
  }
  else if (ledMode == 1){
    pixels.setPixelColor(0, pixels.Color(150, sinAnimateRange(0,40,1), 0)); 
    pixels.show();
  }
  else if (ledMode == 2){ 
    pixels.setPixelColor(0, pixels.Color(150, 150, sinAnimateRange(100,255,1))); 
    pixels.show();
  }
}

float sinAnimateRange(int minVal, int maxVal, float spd){
  float sMill = sin(millis()*spd); // btw -1,1
  sMill = (sMill + 1)/2; //btw 0,1
  sMill = (sMill * (maxVal-minVal)) + minVal;
  return sMill;
}




//      pixels.setPixelColor(0, pixels.Color(150, 0, 0)); // Moderately bright red color.
//      pixels.show(); // This sends the updated pixel color to the hardware.
//      delay(delayval); // Delay for a period of time (in milliseconds).
