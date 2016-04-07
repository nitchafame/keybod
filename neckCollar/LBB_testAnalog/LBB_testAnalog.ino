int prevAnalog0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawAnalog0 = analogRead(A0);

  // zeno smooth
  float speed = 0.1;
  int analog0 = prevAnalog0 * (1 - speed) + rawAnalog0 * speed;
  if (analog0 < 850){
    Serial.println(11);
  }
  else {
    Serial.println(12);
  }
//  Serial.println(analog0);
  

  // if(analog1 > 1000 && analog1 < 1023){
  // Bean.setLed(255, 0, 0);
  // }

  int mappedForLed = map(analog0, 700, 1000, 0, 255);
  Bean.setLed(mappedForLed, 0, 255 - mappedForLed);

  prevAnalog0 = analog0;

  //  Bean.sleep(100);
  delay(1000);
}
