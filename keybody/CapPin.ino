void keyboardCapPin(){
  //-----Capacitive sensing
  for (int i = 0; i < 8; i++) {
    delay(1);
    long start = millis();
    long total =  pins[i].readPin(2000);
    
    // check if we are sensing that a finger is touching && that it wasnt already pressed
    if ((total > THRESH) && (! currentPressed[i]) && (leanCount > 3)) {
      Serial.print("Key pressed #"); Serial.print(i);
      Serial.print(" ("); Serial.print(Keys[i]); Serial.println(")");
      currentPressed[i] = true;
      Keyboard.press(Keys[i]);
    }

    else if ((total <= THRESH) && (currentPressed[i])) {
      // key was released (no touch, and it was pressed before)
      Serial.print("Key released #"); Serial.print(i);
      Serial.print(" ("); Serial.print(Keys[i]); Serial.println(")");
      currentPressed[i] = false;
      Keyboard.release(Keys[i]);
    }
    delay(5);
  }
}


