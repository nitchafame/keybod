
void getA0(){
  
  currentA0 = analogRead(A0);
  
  // calculate zeno smoothed A0
  smoothedA0 = prevA0 * (1 - smoothSpeed) + currentA0 * smoothSpeed;
//  Serial.println(smoothedA0);

  // update for next loop
  prevA0 = smoothedA0;
}


void mapBendInputToLed(){
  
  // map smoothedA0 to LED
  int mappedForLed = map(smoothedA0, 700, 1000, 0, 255);
  Bean.setLed(mappedForLed, 255 - mappedForLed, 0);  
  
  //Text neck posture (bend neck down) : close 1000 : red
  //fixing  posture (look up) : close to 700 : green
  
}

