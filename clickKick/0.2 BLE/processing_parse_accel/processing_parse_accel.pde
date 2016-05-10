import processing.serial.*;

Serial myPort;        // The serial port
int xPosArray[] = {1, 1, 1, 1, 1, 1, 1};
float val[] = {1, 1, 1, 1, 1, 1, 1};

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
  background(#263238);
  strokeWeight(2);
  
}

// -------------------------------
void draw () {
  // everything happens in the serialEvent()
  ellipse(20, 20, random(10,20), random(10,20));
  
  
    // AcX
    stroke(#FF5370);
    line(xPosArray[0], AcX, xPosArray[0]+5, val[0]);
    AcX = val[0];
    // increment the horizontal position:
    xPosArray[0]+=5;
    // at the edge of the screen, go back to the beginning:
    if (xPosArray[0] >= width) {
      xPosArray[0] = 0;
      background(#263238);
    } 


      // AcY
      stroke(#FAD431);
      line(xPosArray[1], AcY, xPosArray[1]+5, val[1]);
      AcY = val[1];
      // increment the horizontal position:
      xPosArray[1]+=5;
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[1] >= width) {
        xPosArray[1] = 0;
        //background(70);
      } 


      // AcZ
      stroke(#C0E88D);
      line(xPosArray[2], AcZ, xPosArray[2]+5, val[2]);
      AcZ = val[2];
      // increment the horizontal position:
      xPosArray[2]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[2] >= width) {
        xPosArray[2] = 0;
        //background(70);
      } 


      // Tmp
      stroke(#CDD3DE);
      line(xPosArray[3], Tmp, xPosArray[3]+5, val[3]);
      Tmp = val[3];
      // increment the horizontal position:
      xPosArray[3]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[3] >= width) {
        xPosArray[3] = 0;
        //background(70);
      } 
      
      
      // GyX
      stroke(#80CBC4);
      line(xPosArray[4], GyX, xPosArray[4]+5, val[4]);
      GyX = val[4];
      // increment the horizontal position:
      xPosArray[4]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[4] >= width) {
        xPosArray[4] = 0;
        //background(70);
      } 



      // GyY
      stroke(#516E7A);
      line(xPosArray[5], GyY, xPosArray[5]+5, val[5]);
      GyY = val[5];
      // increment the horizontal position:
      xPosArray[5]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[5] >= width) {
        xPosArray[5] = 0;
        //background(70);
      } 
      
      
      
      // GyZ
      stroke(#8696BF);
      line(xPosArray[6], GyZ, xPosArray[6]+5, val[6]);
      GyZ = val[6];
      // increment the horizontal position:
      xPosArray[6]+=5;
      
      // at the edge of the screen, go back to the beginning:
      if (xPosArray[6] >= width) {
        xPosArray[6] = 0;
        //background(70);
      } 
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
    float value = float(valString);

  
  
    // draw accelX
    if (label.equals("AcX")) {
  
      val[0] = map(value, -17000, 17000, height, 0);
      println(val);
  
    }
  
    // draw accelY
    if (label.equals("AcY")) {
  
      val[1] = map(value, -17000, 17000, height, 0);
      println(val);
  
    }

    
    
    // draw accelZ
    if (label.equals("AcZ")) {
  
      val[2] = map(value, -17000, 17000, height, 0);
      println(val);
  
    }
    
    
    
    // draw tmp
    if (label.equals("Tmp")) {
  
      val[3] = map(value, -17000, 17000, height, 0);
      println(val);
  
    }
    
        
    // draw GyX
    if (label.equals("GyX")) {
  
      val[4] = map(value, -17000, 17000, height, 0);
      println(val);
  
    }
    
        
    // draw GyY
    if (label.equals("GyY")) {
  
      val[5] = map(value, -17000, 17000, height, 0);
      println(val);
  
    }
    
        
    // draw tmp
    if (label.equals("GyZ")) {
  
      val[6] = map(value, -17000, 17000, height, 0);
      println(val);
  
    }
    
    
  }
  
  
  
}