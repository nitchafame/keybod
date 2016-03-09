void leanEvent(){
  // lean in
  if (AcX > -11000) {
    // haven't count/got notice
    if (!bDidType) {
      leanCount++;
     
      // led notice
      setLedMode(1);
      
      // out once when lean
      
      if (leanCount == 1) {
        Keyboard.println("");  // new line
        Keyboard.println("You’ll get hunchback.");
      }
      else if (leanCount == 2){
        Keyboard.println("");
        Keyboard.println("If you keep hunching like that, you’ll end up with serious condition.");
      }
      
      else if (leanCount == 3){
        Keyboard.println("");
        Keyboard.println("You never listen to me.");
      }
      else if (leanCount == 4){
        Keyboard.println("");
        Keyboard.println("Why do you keep slouching like that?");
      }
      else if (leanCount == 5){
        Keyboard.println("");
        Keyboard.println("Are you noticing your rounded shoulders with your neck protruding forward?");
      }
      else if (leanCount == 6){
        Keyboard.println("");
        Keyboard.println("This will forces your chest muscles to tighten,");
        Keyboard.println("which pulls your spine forward and rotates your shoulders inward,");
        Keyboard.println("while at the same time weakening the muscles of your upper back that aid in posture.");
        leanCount = 0;
      }
      
      
      bDidType = true;
    }
  }
  // lean out
  else {
    bDidType = false;
    setLedMode(0);
    //      Keyboard.println("Good");
  }
  
  // continuous habit while lean 
  if (leanCount == 1) {
    //setLedMode(2);
    
  } else {

  }
}
