void setLedMode(int mode){
  ledMode = mode;
}

void ledUpdate(){
  if (ledMode == 0){
    float r = sinAnimateRange(20,100,.0005);
    float g = sinAnimateRange(5,100,.001);
    float b = sinAnimateRange(0,100,.002);
    pixels.setPixelColor(0, pixels.Color(r, g, b)); 
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
  
  
//  switch(ledMode){
//    case 0: 
//            pixels.setPixelColor(0, pixels.Color(sinAnimateRange(20,255,1), 0, 0)); 
//            pixels.show();
//            break;
//    case 1: 
//            pixels.setPixelColor(0, pixels.Color(150, sinAnimateRange(0,40,1), 0)); 
//            pixels.show();
//            break;
//    case 2: pixels.setPixelColor(0, pixels.Color(150, 150, sinAnimateRange(100,255,1))); 
//            pixels.show();
//            break;
//  }
}

float sinAnimateRange(int minVal, int maxVal, float spd){
  float sMill = sin(millis()*spd); // btw -1,1
  sMill = (sMill + 1)/2; //btw 0,1
  sMill = (sMill * (maxVal-minVal)) + minVal;
  return sMill;
}




  //  for(int i=0;i<NUMPIXELS;i++){
  //    pixels.setPixelColor(i, pixels.Color(0,150,0));
  //    pixels.show();
  //    delay(delayval);
  //  }
