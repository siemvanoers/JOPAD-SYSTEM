const int ledPins[] = {1, 3, 5, 7, 9, 11};
int potentiometerPin = A5;
int totalLeds = 6;
int delay = 50;

void setup() {
  // Stel elke LED-pin in als output
  for (int i = 0; i < totalLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // Stel de potentiometerpin in als input
  pinMode(potentiometerPin, INPUT);  
}

void loop() {
  // Roep de functie aan om de input en LED-besturing te verwerken met een vertraging van 50ms
  updateLeds(50); 
}

void updateLeds(int delay) {
  // Lees de potentiometerwaarde
  int potValue = analogRead(potentiometerPin);
  // Map de potentiometerwaarde naar de LED-drempel
  int limit = map(potValue, 0, 1023, totalLeds, 0); 

  // Update de LED-statussen
  for (int i = 0; i < totalLeds; i++) {
    if (i < limit) {
      // Zet de LED aan
      digitalWrite(ledPins[i], LOW); 
    } else {
      // Zet de LED uit
      digitalWrite(ledPins[i], HIGH);
    }
  }
  // Voeg een korte vertraging toe om het goed te laten werken
  delay(delay);  
}
