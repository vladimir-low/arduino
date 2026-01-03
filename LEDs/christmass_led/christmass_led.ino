/* Christmass tree LED blinking
LEDs are set on the tips of the 2-story tree


*/

// constants
const int ledPins [] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};  // output ports at board
const int numPins = 10;

void setup() {
 for (int i=0;i<numPins;i++)
   pinMode(ledPins[i], OUTPUT); 
}

void blinkSeq() {
 for (int i=0;i<numPins;i++) {
   digitalWrite(ledPins[i], HIGH);
   delay(100);
   digitalWrite(ledPins[i], LOW);
   delay(100);
 } 
}

void blinkPairs() {
  for (int i=0;i<numPins/2;i++) {
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[numPins-1-i], HIGH);
    delay(500);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[numPins-1-i], LOW);
    delay(500);
  }
}

void blinkAll() {
  for (int j=0;j<3;j++) {
    for (int i=0;i<numPins;i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(500);
    for (int i=0;i<numPins;i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(500);
  }
}

void loop() {
 blinkSeq();
 delay(2000);
 blinkPairs();
 delay(2000);
 blinkAll();
 delay(2000);
}
