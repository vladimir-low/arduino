/*
 * Blinking with turn signals in Ford Mustang style
 * 
 * There is 4 segments LED is used on each side
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

// Output Pins
const int leftOut1 = 3;
const int leftOut2 = 4;
const int leftOut3 = 5;
const int leftOut4 = 6;
const int rightOut1 = 7;
const int rightOut2 = 8;
const int rightOut3 = 9;
const int rightOut4 = 10;
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
  attachInterrupt(digitalPinToInterrupt(brakesIn), brake, RISING);
}

void leftOn() {
  for (int i=1; i<=4; i++) {
    digitalWrite("leftOut" + i, HIGH);
  }
}

void rightOn() {
  for (int i=1; i<=4; i++) {
    digitalWrite("rightOut" + i, HIGH);
  }
}

void leftOff() {
  for (int i=1; i<=4; i++)
    digitalWrite("leftOut" + i, LOW);
}

void rightOff() {
  for (int i=1; i<=4; i++)
    digitalWrite("rightOut" + i, LOW);
}

void leftBlink() {
  for (int i=1; i<=4; i++) {
    digitalWrite("leftOut" + i, HIGH);
    delay(300);
  }
  delay(100);
}

void rightBlink() {
  for (int i=1; i<=4; i++) {
    digitalWrite("rightOut" + i, HIGH);
    delay(300);
  }
  delay(100);
}

void hazardFlash() {
  for (int i=1; i<=4; i++) {
    digitalWrite("leftOut" + i, HIGH);
    digitalWrite("rightOut" + i, HIGH);
    delay(500);
  }
  for (int i=1; i<=4; i++) {
    digitalWrite("leftOut" + i, LOW;
    digitalWrite("rightOut" + i, LOW);
    delay(300);
  }
}

void stopFlash() {
  for (int i=1; i<=4; i++) {
    digitalWrite("leftOut" + i, HIGH);
    digitalWrite("rightOut" + i, HIGH);
  }
  delay(100);
  for (int i=1; i<=4; i++) {
    digitalWrite("leftOut" + i, LOW;
    digitalWrite("rightOut" + i, LOW);
  }
  delay(60);
}

// Brakes interrupt handling (see table above)
void brake() {
  isBrake = HIGH;
  for (i=0; i<3; i++) {
    stopFlash();
  }
  while (isBrake = HIGH) {
    for (int i==0; i<=5; i++) {
      isBrake = digitalRead(brakeIn);
      isLeftTurn = digitalRead(leftIn);
      isRightTurn = digitalRead(rightIn);
      delay(10);
    }
    // Left turn
    if ((isLeftTurn = HIGH) && (isRightTurn = LOW)) {
      rightOn();    
      leftBlink();
    }
    // Right turn 
    else if ((isRightTurn = HIGH) && (isLeftTurn = LOW)) {
      leftOn();
      rightBlink();
    }
    // Pure braking
    else if ((isLeftTurn = LOW) && (isRightTurn = LOW)) {
      leftOn();
      rightOn();
      delay(5000);
    }   
  }
  isBrake = LOW;
}

void loop() {
  // read the state of turns. Loop is used to eliminate chatter.
  for (int i==0; i<=5; i++) {
    isLeftTurn = digitalRead(leftIn);
    isRightTurn = digitalRead(rightIn);
    delay(10);
  }
  // Left turn
  if ((isLeftTurn = HIGH) && (isRightTurn = LOW)) {
    leftBlink();
  }
  // Right turn 
  else if ((isRightTurn = HIGH) && (isLeftTurn = LOW)) {
    rightBlink();
  }
  // Hazard warning
  else if ((isLeftTurn = HIGH) && (isRightTurn = HIGH)) {
    hazardFlash();
  }
}
