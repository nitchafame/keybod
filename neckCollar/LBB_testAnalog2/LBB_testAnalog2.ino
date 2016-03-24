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
  Serial.println(analog0);

  int mappedForLed = map(analog0, 700, 1000, 0, 255);
  Bean.setLed(mappedForLed, 0, 255 - mappedForLed);

  prevAnalog0 = analog0;

  //  Bean.sleep(100);

}
