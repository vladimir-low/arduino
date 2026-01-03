/* Multiple LED blinking
 with button. Traffic light emulation
 
 Vladimir Malyarevich, 2015
*/

// --- Constants ---
const int redPin = 11;
const int ylwwPin = 12;
const int greenPin = 13;
const int pedWhitePin = 9;
const int pedRedPin = 10;
const int buttonPin = 2;

// --- Time Settings (Milliseconds) ---
const int redInterval = 5000;
const int greenInterval = 10000;
const int ylwInterval = 2000;
const int pedInterval = 500;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(ylwwPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(pedWhitePin, OUTPUT);
  pinMode(pedRedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  digitalWrite(pedRedPin, HIGH);  // Ped Red light on  

  // Traffic light blinking 
  int interval, buttonState;
  for (int i=0;i<3;i++) {
    buttonState = digitalRead(buttonPin);  // Get button state
    digitalWrite(redPin, HIGH);
    delay(redInterval);
    digitalWrite(ylwwPin, HIGH);
    delay(ylwInterval);
    digitalWrite(redPin, LOW);
    digitalWrite(ylwwPin, LOW);
    digitalWrite(greenPin, HIGH);
    delay(greenInterval);
    digitalWrite(greenPin, LOW);
    digitalWrite(ylwwPin, HIGH);
    delay(ylwInterval);
    digitalWrite(ylwwPin, LOW);
  }

  // Process pedestrian button state:
  if (buttonState == HIGH) {
    digitalWrite(redPin, HIGH); // Car red light on
    digitalWrite(pedRedPin, LOW);  // Ped red light off
    // blink ped white light
    for (int x=0;x<=20;x++) {
      digitalWrite(pedWhitePin, HIGH);
      delay(pedInterval);
      digitalWrite(pedWhitePin, LOW);
      delay(pedInterval);
    }
  }
  digitalWrite(redPin, LOW); // Car red light on
 }
