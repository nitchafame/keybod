import processing.serial.*;
float pitch, roll;
float position;
Serial myPort;

void setup() {
  size(400, 400, P3D);
  position = width/2;
  println(Serial.list());
  
  myPort = new Serial(this, Serial.list()[2], 9600);
  myPort.bufferUntil('\n');
}

void draw () {
  background(#20542E);
  println(pitch + "," + roll);
  tilt();
}


void tilt() {
  pushMatrix();
  translate(position, position, position);
  rotateX(radians(roll + 90));
  rotateY(radians(pitch) );
  fill(#79BF3D);
  ellipse(0, 0, width/4, width/4);
  fill(#20542E);
  text(pitch + "," + roll, -40, 10, 1);
  popMatrix();
}

void serialEvent(Serial myPort) {
  String myString = myPort.readStringUntil('\n');
  if (myString != null) {
    myString = trim(myString);
    String items[] = split(myString, ',');
    if (items.length > 1) {
      pitch = float(items[0]);
      roll = float(items[1]);
    }
  }
}