const int pinArray[] = {13, 12, 11, 10, 9, 5, 3, 1};

void setup() {
  for (int count = 0; count < 8; count++) {
    pinMode(pinArray[count], OUTPUT);
	}
}

void loop() {
  int tijd = 50;  // Default delay time in milliseconds
  
  for (int count = 0; count < 8; count++) {
    digitalWrite(pinArray[count], HIGH);
    delay(tijd);
    digitalWrite(pinArray[count], LOW);
    delay(tijd);
  }
  
  for (int count = 7; count >= 0; count--) {
    digitalWrite(pinArray[count], HIGH);
    delay(tijd);
    digitalWrite(pinArray[count], LOW);
    delay(tijd);
  }
}
