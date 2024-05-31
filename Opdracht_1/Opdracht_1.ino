const int pinArray[] = {13, 10};

void setup() {
  for (int count; count < 2; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
}

void loop() {
  int time = 1500;

  digitalWrite(13, HIGH);
  delay(time);
  digitalWrite(13, LOW);
  digitalWrite(10, HIGH);
  delay(time);
  digitalWrite(10, LOW);
}
