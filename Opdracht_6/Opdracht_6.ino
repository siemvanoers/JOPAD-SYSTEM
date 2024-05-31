#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int button1Pin = 2;   
const int button2Pin = 13; 
// I2C adres, aantal kolommen, aantal rijen
LiquidCrystal_I2C lcd(0x27, 16, 2); 
// Variabele om starttijd in op te slaan
unsigned long startingTime = 0;
// Variabele om vorige stopwatch tijd in op te slaan
unsigned long previousTime = 0;
// Variabele om op te slaan wanneer knop 1 voor het eerst was ingedrukt
unsigned long button1TimePress = 0;    
// Variabele om op te slaan of de stopwatch aan het lopen is of niet
bool isRunning = false;
// Variabele om op te slaan wanneer de knop is ingedrukt
unsigned long buttonPressedTime = 0; 

void setup() {
  // Definieer pinmode
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // stel LCD in
  lcd.init();
  // Zet backlight aan
  lcd.backlight();
  // Plaats cursor op rij 1
  lcd.setCursor(0, 0);
  // Print tijdformaat
  lcd.print("00:00.000");
  // Start timer
  startingTime = millis(); 
}

void loop() {
  // Lees de status van knoppen als boolean
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  // Controleer of knop 1 is ingedrukt
  if (button1State == HIGH) {
    // Als druk tijd nog niet is opgeslagen
    if (button1TimePress == 0) { 
      // Sla op wanneer knop voor het eerst is ingedrukt
      button1TimePress = millis(); 
      // Controleer of knop voor 2 seconden of langer is ingedrukt
    } else if (millis() - button1TimePress >= 2000) { 
      // Toon ronde
      displayLap();
      // Reset knop tijd 
      button1TimePress = 0; 
    }
    if (!isRunning) {
      // Start de stopwatch
      isRunning = true; 
      // Sla de starttijd op
      startingTime = millis(); 
      // Vertraging voor betere gebruikerservaring
      delay(100); 
    }
  } else {
    // Reset knop loslaten tijd
    button1TimePress = 0; 
  }

  // Controleer of knop 2 is ingedrukt om de stopwatch te resetten 
  if (button2State == HIGH) {
    isRunning = false;
  }

  // Vertraging om de Arduino tijd te geven om te controleren of er op twee knoppen wordt gedrukt 
  delay(100);
    
  // Controleer of er op twee knoppen tegelijk wordt gedrukt
  if (button1State && button2State) {
    // Wis LCD
    lcd.clear();
    // Plaats cursor op rij 1
    lcd.setCursor(0, 0);
    // Print tijdformaat
    lcd.print("00:00:00.000");
  }

  // Werk scherm alleen bij als de stopwatch loopt
  if (isRunning) {
    displayTime();
  }
}

void displayTime() {
  unsigned long currentTime = millis() - startingTime;
  // Haal milliseconden op
  unsigned long milliseconds = currentTime % 1000; 
  // Bereken totale seconden
  unsigned long seconds = currentTime / 1000;
  // Bereken minuten
  unsigned long minutes = seconds / 60;
  // Bereken uren

  // Pas seconden, minuten en uren aan om binnen bereik te blijven
  seconds %= 60;
  minutes %= 60;

  // Print tijd in "00:00.000" formaat
  lcd.setCursor(0, 0);
  lcd.print(minutes < 10 ? "0" : "");
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(seconds < 10 ? "0" : "");
  lcd.print(seconds);
  lcd.print(".");
  lcd.print(milliseconds < 100 ? "0" : ""); 
  lcd.print(milliseconds < 10 ? "0" : "");
  lcd.print(milliseconds);
}

void displayLap(){
  // Bereken verstreken tijd
  unsigned long currentTime = (millis() - 2000) - startingTime; 
  // Haal milliseconden op
  unsigned long milliseconds = currentTime % 1000; 
  // Bereken totale seconden
  unsigned long seconds = currentTime / 1000; 
  // Bereken minuten
  unsigned long minutes = seconds / 60; 

  // Pas seconden en minuten aan om binnen bereik te blijven
  seconds %= 60;
  minutes %= 60;

  // Print verstreken tijd in "00:00.000" formaat
  lcd.setCursor(0, 1);
  if (minutes < 10) lcd.print("0"); 
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0"); 
  lcd.print(seconds);
  lcd.print(".");
  lcd.print(milliseconds < 100 ? "0" : ""); 
  lcd.print(milliseconds < 10 ? "0" : "");
  lcd.print(milliseconds);
}
