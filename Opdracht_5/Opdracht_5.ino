#include <Servo.h>

const int button1Pin = 3;  
const int button2Pin = 10; 
const int servoPin = 0; 

Servo myServo;

void setup() {
  // Stel pinmode in voor de knoppen
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // Koppel de servomotor aan de pin
  myServo.attach(servoPin);
}

void loop() {
  // Lees de state van de knoppen
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  // Vertraging om de Arduino de tijd te geven om een dubbele klik te controleren
  delay(200);

  // Controleer dubbele klik
  if (button1State && button2State) {
    // Beweeg de servo in 5s, wacht 2s, en keer terug in 0.5s
    controlServo(0, 120, 5000);
    delay(2000);
    controlServo(120, 0, 500);
  }
  // Controleer of knop 1 is ingedrukt
  else if (button1State) {
    // Beweeg de servo in 5s, en keer terug in 5s
    controlServo(0, 120, 5000);
    controlServo(120, 0, 5000);
  } 
  // Controleer of knop 2 is ingedrukt
  else if (button2State) {
    // Beweeg de servo in 0.5s, en keer terug in 0.5s
    controlServo(0, 120, 500);
    controlServo(120, 0, 500);
  }
}

// Functie om de servo te bewegen
void controlServo(int startAngle, int endAngle, int duration) {
  // Bereken interval
  int interval = calculateInterval(startAngle, endAngle, duration);

  if (startAngle < endAngle) {
    // Als de beginhoek kleiner is dan de eindhoek,
    // beweeg de servo van de beginhoek naar de eindhoek in toenemende volgorde.
    for (int angle = startAngle; angle <= endAngle; angle++) {
        // Schrijf de huidige hoekwaarde naar de servomotor
        myServo.write(angle);
        // Wacht de opgegeven interval tot je verder gaat
        delay(interval);
    }
  } else {
    // Als de beginhoek groter of gelijk is aan de eindhoek,
    // beweeg de servo van de beginhoek naar de eindhoek in afnemende volgorde.
    for (int angle = startAngle; angle >= endAngle; angle--) {
        // Schrijf de huidige hoekwaarde naar de servomotor
        myServo.write(angle);
        // Wacht de opgegeven interval tot je verder gaat
        delay(interval);
    }
  }
}

// Functie om interval te berekenen
int calculateInterval(int startAngle, int endAngle, int duration) {
  return duration / abs(endAngle - startAngle);
}
