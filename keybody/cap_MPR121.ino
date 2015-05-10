void setupCap(){
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  //set touch threshholds (touch, release) - - - default (12, 6);
  cap.setThreshholds(40, 6);
}
// --------
void setupCap2(){
  Serial.println("Adafruit MPR121(2) Capacitive Touch sensor test"); 

  if (!cap2.begin(0x5B)) {
    Serial.println("MPR121(2) not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121(2) found!");
}
// --------
void setupCap3(){
  Serial.println("Adafruit MPR121(3) Capacitive Touch sensor test"); 

  if (!cap3.begin(0x5C)) {
    Serial.println("MPR121(3) not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121(3) found!");
}


// ------------------------------------------------------------------
void keyInputCap(){
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
//      if( i == 0 ) Keyboard.press('');
//      else if ( i == 1 ) Keyboard.press('');
      if ( i == 2 ) Keyboard.press('d');
      else if ( i == 3 ) Keyboard.press('s');
      else if ( i == 4 ) Keyboard.press('x');
//      else if ( i == 5 ) Keyboard.press('');
      else if ( i == 6 ) Keyboard.press('s');
      else if ( i == 7 ) Keyboard.press('q');
      else if ( i == 8 ) Keyboard.press(KEY_BACKSPACE);
      else if ( i == 9 ) Keyboard.press('j');
      else if ( i == 10 ) Keyboard.press('k');
      else if ( i == 11 ) Keyboard.press('e');
      else Serial.print("invalid cap(1) press input");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
//      if( i == 0 ) Keyboard.release('');
//      else if ( i == 1 ) Keyboard.release('');
      if ( i == 2 ) Keyboard.release('d');
      else if ( i == 3 ) Keyboard.release('s');
      else if ( i == 4 ) Keyboard.release('x');
//      else if ( i == 5 ) Keyboard.release('');
      else if ( i == 6 ) Keyboard.release('s');
      else if ( i == 7 ) Keyboard.release('q');
      else if ( i == 8 ) Keyboard.release(KEY_BACKSPACE);
      else if ( i == 9 ) Keyboard.release('j');
      else if ( i == 10 ) Keyboard.release('k');
      else if ( i == 11 ) Keyboard.release('e');
      else Serial.print("invalid cap(1) release input");
    }
  }

  // reset our state
  lasttouched = currtouched;
}
// --------
void keyInputCap2(){
  currtouched2 = cap2.touched();
 
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched2 & _BV(i)) && !(lasttouched2 & _BV(i)) ) {
      Serial.print(i); Serial.println("(2) touched");
      if( i == 0 ) Keyboard.press('f');
      else if ( i == 1 ) Keyboard.press('h');
      else if ( i == 2 ) Keyboard.press('g');
      else if ( i == 3 ) Keyboard.press('b');
      else if ( i == 4 ) Keyboard.press('y');
      else if ( i == 5 ) Keyboard.press('w');
      else if ( i == 6 ) Keyboard.press('o');
      else if ( i == 7 ) Keyboard.press('r');
      else if ( i == 8 ) Keyboard.press('a');
      else if ( i == 9 ) Keyboard.press('m');
//      else if ( i == 10 ) Keyboard.press('');
//      else if ( i == 11 ) Keyboard.press('');
      else Serial.print("invalid cap(2) press input");
    }
    if (!(currtouched2 & _BV(i)) && (lasttouched2 & _BV(i)) ) {
      Serial.print(i); Serial.println("(2) released");
      if( i == 0 ) Keyboard.release('f');
      else if ( i == 1 ) Keyboard.release('h');
      else if ( i == 2 ) Keyboard.release('g');
      else if ( i == 3 ) Keyboard.release('b');
      else if ( i == 4 ) Keyboard.release('y');
      else if ( i == 5 ) Keyboard.release('w');
      else if ( i == 6 ) Keyboard.release('o');
      else if ( i == 7 ) Keyboard.release('r');
      else if ( i == 8 ) Keyboard.release('a');
      else if ( i == 9 ) Keyboard.release('m');
//      else if ( i == 10 ) Keyboard.release('');
//      else if ( i == 11 ) Keyboard.release('');
      else Serial.print("invalid cap(2) release input");
    }
  }

  lasttouched2 = currtouched2;
}
// --------
void keyInputCap3(){
  currtouched3 = cap3.touched();
  
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched3 & _BV(i)) && !(lasttouched3 & _BV(i)) ) {
      Serial.print(i); Serial.println("(3) touched");
//      if( i == 0 ) Keyboard.press('');
//      else if ( i == 1 ) Keyboard.press('');
//      else if ( i == 2 ) Keyboard.press('');
//      else if ( i == 3 ) Keyboard.press('');
//      else if ( i == 4 ) Keyboard.press('');
      if ( i == 5 ) Keyboard.press('i');
      else if ( i == 6 ) Keyboard.press('t');
      else if ( i == 7 ) Keyboard.press('c');
      else if ( i == 8 ) Keyboard.press('u');
//      else if ( i == 9 ) Keyboard.press('');
//      else if ( i == 10) Keyboard.press('');
//      else if ( i == 11) Keyboard.press('');
      else Serial.print("invalid cap(3) press input");
    }
    if (!(currtouched3 & _BV(i)) && (lasttouched3 & _BV(i)) ) {
      Serial.print(i); Serial.println("(3) released");
//      if( i == 0 ) Keyboard.release('');
//      else if ( i == 1 ) Keyboard.release('');
//      else if ( i == 2 ) Keyboard.release('');
//      else if ( i == 3 ) Keyboard.release('');
//      else if ( i == 4 ) Keyboard.release('');
      if ( i == 5 ) Keyboard.release('i');
      else if ( i == 6 ) Keyboard.release('t');
      else if ( i == 7 ) Keyboard.release('c');
      else if ( i == 8 ) Keyboard.release('u');
//      else if ( i == 9 ) Keyboard.release('');
//      else if ( i == 10) Keyboard.release('');
//      else if ( i == 11) Keyboard.release('');
      else Serial.print("invalid cap(3) release input");
    }
  }

  lasttouched3 = currtouched3;
}


// ------------------------------------------------------------------
void printCapDebug(){ 
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); 
  Serial.println(cap.touched(), HEX);
  
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}
