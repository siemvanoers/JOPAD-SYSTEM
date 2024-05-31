const int led1 = 10;
const int led2 = 8;
const int buttonPin = 12;

int buttonState = 0;
int lastButtonState = 0;
int counter = 0;

void setup() {
  pinMode(led1, OUTPUT);  // Stel LED 1 in als output
  pinMode(led2, OUTPUT);  // Stel LED 2 in als output
  pinMode(buttonPin, INPUT);  // Stel de knop in als input
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Lees de status van de knop

  // Controleer of de knop is ingedrukt
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      // Als de huidige status HIGH is, dan is de knop van uit naar aan gegaan
      counter++;
      // Roep de functie aan om de LEDs bij te werken op basis van de tellerwaarde
      updateLeds(counter);
      delay(50); // Vertraging voor debouncing
    }
  }
  lastButtonState = buttonState; // Sla de huidige status op als de laatste status
}

// Functie om de LEDs bij te werken op basis van de counter
void updateLeds(int count) {
  if (count % 2 == 0) {
    digitalWrite(led1, LOW);  // Zet LED 1 uit
    digitalWrite(led2, HIGH); // Zet LED 2 aan
  } else {
    digitalWrite(led1, HIGH); // Zet LED 1 aan
    digitalWrite(led2, LOW);  // Zet LED 2 uit
  }
}
