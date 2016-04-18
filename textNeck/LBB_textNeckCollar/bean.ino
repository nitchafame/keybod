
void wakeUpRoutine() {
  // sth to do right after waking up
  Bean.setLed(0, 255, 0);
  Bean.sleep(100);
  Bean.setLed(0, 0, 0);
}

