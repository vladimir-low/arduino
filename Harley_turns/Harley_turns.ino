/*
 * Blinking with turn signals in Ford Mustang style
 * 
 * 4 segments LED is used on each side
 * 
 * STOP signal should be handled immediately. 
 * PD2 (INT0) will be use for this purpose (external interrupt)
 * 
 * Use cases are described in the table below:
 * -------------------------------------------------------------------------
 * | Left Turn | Right Turn | Stop |               Action                  |
 * -------------------------------------------------------------------------
 * |   V       |      -     |   -  | Left side LEDs blinking sequentially  |
 * -------------------------------------------------------------------------
 * |   -       |      V     |   -  | Right side LEDs blinking sequentially |
 * -------------------------------------------------------------------------
 * |   V       |      V     |   -  | Hazard warning mode. Both sides LEDs  |
 * |           |            |      | are blinking synchronousely           |
 * -------------------------------------------------------------------------
 * |    -      |      -     |   V  | Brake mode. Both sides LEDs flash for |
 * |           |            |      | for 0.5 sec. Then both are ON         |
 * -------------------------------------------------------------------------
 * |  V (-)    |   - (V)    |   V  | Braking when turning. Both sides LEDs |
 * |           |            |      | flash for 0.5 sec. Then LED of the    |
 * |           |            |      | turn direction blinking sequentially. |
 * |           |            |      | LEDs from the opposite side is ON     |
 * ------------------------------------------------------------------------|
 * 
*/

// Output start pin and LED segments amount
const int leftOutFirstPin = 3;
const int rightOutFirstPin = 7;
const int ledsAmount = 4;
// Input Pins
const int leftIn = 0;
const int rightIn = 1;
const int brakeIn = 2;

// Variables
volatile int isBrake = LOW;
volatile int isLeftTurn = LOW;
volatile int isRightTurn = LOW;

// function runs once when you press reset or power the board
void setup() {
  for (int i=0; i<=2; i++) {
    pinMode(i, INPUT);
  }
  for (int i=3; i<=10; i++) {
    pinMode(i, OUTPUT);
  }
  //Interrupts the main loop when HIGH level appears in the pin
  attachInterrupt(digitalPinToInterrupt(brakeIn), brake, RISING);
}

void leftOn() {
  for (int i=0; i<ledsAmount; i++) {
    digitalWrite(leftOutFirstPin + i, HIGH);
  }
}

void rightOn() {
  for (int i=0; i<ledsAmount; i++) {
    digitalWrite(rightOutFirstPin + i, HIGH);
  }
}

void leftOff() {
  for (int i=0; i<ledsAmount; i++)
    digitalWrite(leftOutFirstPin + i, LOW);
}

void rightOff() {
  for (int i=0; i<ledsAmount; i++)
    digitalWrite(rightOutFirstPin + i, LOW);
}

void leftBlink() {
  for (int i=0; i<ledsAmount; i++) {
    digitalWrite(leftOutFirstPin + i, HIGH);
    delay(300);
  }
  delay(100);
  leftOff();
}

void rightBlink() {
  for (int i=0; i<ledsAmount; i++) {
    digitalWrite(rightOutFirstPin + i, HIGH);
    delay(300);
  }
  delay(100);
  rightOff();
}

void hazardFlash() {
  leftOn();
  rightOn();
  delay(500);
  leftOff();
  rightOff();
  delay(300);
}

// Flash rapidly with both sides
void stopFlash() {
  for (int i=0; i<5; i++) {
    leftOn();
    rightOn();
    delay(120);
    leftOff();
    rightOff();
    delay(80);
  }
}

// Brakes interrupt handling (see table above)
void brake() {
  stopFlash();
  isBrake = HIGH;
}

void loop() {
  // read the state of turns. Loop is used to eliminate chatter.
  for (int i=0; i<=5; i++) {
    isLeftTurn = digitalRead(leftIn);
    isRightTurn = digitalRead(rightIn);
    isBrake = digitalRead(brakeIn);
    delay(10);
  }
  switch (isBrake) {
    case HIGH: // when brakes are still pressed...
      // and Left turn
      if ((isLeftTurn == HIGH) && (isRightTurn == LOW)) {
        rightOn();
        leftBlink();
        break;
      }
      // and Right turn
      else if ((isRightTurn == HIGH) && (isLeftTurn == LOW)) {
        leftOn();
        rightBlink();
        break;
      }
      // and No turns
      else if ((isLeftTurn == LOW) && (isRightTurn == LOW)) {
        leftOn();
        rightOn();
        break;
      }
     case LOW: // No braking
      // Left turn
      if ((isLeftTurn == HIGH) && (isRightTurn == LOW)) {
        leftBlink();
        break;
      }
      // Right turn
      else if ((isRightTurn == HIGH) && (isLeftTurn == LOW)) {
        rightBlink();
        break;
      }
      // Hazard warning
      else if ((isLeftTurn == HIGH) && (isRightTurn == HIGH)) {
        hazardFlash();
      }
    }
}
