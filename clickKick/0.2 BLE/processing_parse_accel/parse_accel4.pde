import processing.serial.*;

Serial myPort;        // The serial port
int xPosArray[] = {1, 1, 1, 1, 1, 1, 1};

float value=0;
float AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// -------------------------------
void setup () {
  // set the window size:
  size(1000, 200);

  // List all the available serial ports
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[5], 115200);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('|');
  background(70);
}

// -------------------------------
void draw () {
  // everything happens in the serialEvent()
  rect(0,0,10,10);

}

// -------------------------------
void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('|');
  String items[] = split(inString, '=');
  // AcX
  // AcY
  // AcZ
  // Tmp
  // GyX
  // GyY
  // GyZ

  // PARSE Serial input
  // if there was more than one string after the split
  if (items.length > 1) {
    String label = trim(items[0]);
    String valRaw = split(items[1], '|')[0];
    String valString = trim(valRaw);
    float val = float(valString);
  
  
  
    // draw accelX
    if (label.equals("AcX")) {
      print("AcX = ");
      println(val);
      val = map(val, -150, 150, height, 0);
  
      // draw
      stroke(#cc0000);
      line(xPosArray[0], AcX, xPosArray[0]+5, val);
      AcX = val;
      // increment the horizontal position:
      xPosArray[0]+=5;
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[0] >= width) {
        xPosArray[0] = 0;
        background(70);
      } 
    }
  
    // draw accelY
    if (label.equals("AcY")) {
      print("AcY = ");
      println(val);
      val = map(val, -150, 150, height, 0);
  
      // draw
      stroke(#669900);
      line(xPosArray[1], AcY, xPosArray[1]+5, val);
      AcY = val;
      // increment the horizontal position:
      xPosArray[1]+=5;
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[1] >= width) {
        xPosArray[1] = 0;
        //background(70);
      } 
    }

    
    
    // draw accelZ
    if (label.equals("AcZ")) {
      print("AcZ = ");
      println(val);
      val = map(val, -150, 150, height, 0);
  
      // draw
      stroke(#006699);
      line(xPosArray[2], AcZ, xPosArray[2]+5, val);
      AcZ = val;
      // increment the horizontal position:
      xPosArray[2]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[2] >= width) {
        xPosArray[2] = 0;
        //background(70);
      } 
    }
    
    
    
    // draw tmp
    if (label.equals("Tmp")) {
      print("Tmp = ");
      println(val);
      val = map(val, 30, 45, height, 0);
  
      // draw
      stroke(255);
      line(xPosArray[3], Tmp, xPosArray[3]+5, val);
      Tmp = val;
      // increment the horizontal position:
      xPosArray[3]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[3] >= width) {
        xPosArray[3] = 0;
        //background(70);
      } 
    }
    
        
    // draw GyX
    if (label.equals("GyX")) {
      print("GyX = ");
      println(val); 
      val = map(val, -150, 150, height, 0);
      
      // draw
      stroke(#6E0000);
      line(xPosArray[4], GyX, xPosArray[4]+5, val);
      GyX = val;
      // increment the horizontal position:
      xPosArray[4]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[4] >= width) {
        xPosArray[4] = 0;
        //background(70);
      } 
    }
    
        
    // draw GyY
    if (label.equals("GyY")) {
      print("GyY = ");
      println(val);
      val = map(val, -150, 150, height, 0);
  
      // draw
      stroke(#244700);
      line(xPosArray[5], GyY, xPosArray[5]+5, val);
      GyY = val;
      // increment the horizontal position:
      xPosArray[5]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[5] >= width) {
        xPosArray[5] = 0;
        //background(70);
      } 
    }
    
        
    // draw tmp
    if (label.equals("GyZ")) {
      print("GyZ = ");
      println(val);
      val = map(val, -150, 150, height, 0);
  
      // draw
      stroke(#003366);
      line(xPosArray[6], GyZ, xPosArray[6]+5, val);
      GyZ = val;
      // increment the horizontal position:
      xPosArray[6]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[6] >= width) {
        xPosArray[6] = 0;
        //background(70);
      } 
    }
    
    
  }
  
  
  
}