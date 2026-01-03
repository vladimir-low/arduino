/* Smart Traffic Light v2
   Fixes the "Floating Pin" issue using INPUT_PULLUP.
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
  
  // FIX: Use INPUT_PULLUP to prevent random noise triggers
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  // Ensure Pedestrian lights are in "Don't Walk" state during normal traffic
  digitalWrite(pedWhitePin, LOW);
  digitalWrite(pedRedPin, HIGH);

  // 1. CARS: RED LIGHT
  digitalWrite(redPin, HIGH);
  if(smartDelay(redInterval)) { runPedestrianMode(); return; }

  // 2. CARS: YELLOW LIGHT
  digitalWrite(ylwwPin, HIGH);
  if(smartDelay(ylwInterval)) { runPedestrianMode(); return; } 
  digitalWrite(ylwwPin, LOW);
  digitalWrite(redPin, LOW);

  // 3. CARS: GREEN LIGHT
  digitalWrite(greenPin, HIGH);
  if(smartDelay(greenInterval)) {
    delay(2000); 
    digitalWrite(greenPin, LOW); 
    runPedestrianMode(); 
    return; 
  }
  digitalWrite(greenPin, LOW);

  // 4. CARS: YELLOW LIGHT
  digitalWrite(ylwwPin, HIGH);
  if(smartDelay(ylwInterval)) { runPedestrianMode(); return; } 
  digitalWrite(ylwwPin, LOW);
}

// --- Helper Functions ---

/* smartDelay: Replaces standard delay().
   Returns TRUE if button was pressed (Active LOW).
   Returns FALSE if time ran out.
*/
bool smartDelay(int duration) {
  unsigned long startTime = millis();
  
  while (millis() - startTime < duration) {
    // FIX: Check for LOW because we are using INPUT_PULLUP
    // LOW means the button connects the pin to Ground (Pressed)
    if (digitalRead(buttonPin) == LOW) {
      return true; 
    }
  }
  return false; 
}

/*
   The sequence that runs when the button is pressed
*/
void runPedestrianMode() {
  // 1. Safety: Turn off Green/Yellow, Turn on Car Red
  digitalWrite(greenPin, LOW);
  digitalWrite(ylwwPin, LOW);
  digitalWrite(redPin, HIGH); 
  
  // 2. Pedestrian Sequence
  digitalWrite(pedRedPin, LOW); // Ped Red OFF
  
  // Blink Pedestrian White Light
  for (int x = 0; x <= 10; x++) {
    digitalWrite(pedWhitePin, HIGH);
    delay(pedInterval); 
    digitalWrite(pedWhitePin, LOW);
    delay(pedInterval);
  }
  
  // 3. Reset to safe state (Ped Red ON, Car Red stays on until loop restarts)
  digitalWrite(pedRedPin, HIGH); 
  digitalWrite(redPin, LOW);     
}