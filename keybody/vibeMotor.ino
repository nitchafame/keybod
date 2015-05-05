void setVibeMode(int mode){
  vibeMode = mode;
}

void vibeUpdate(){
  // animate vibe
  if (vibeMode == 0){
    vibeVal = sinAnimateRange(0,255,1);  
  }
  analogWrite(vibePin, vibeVal);
}
