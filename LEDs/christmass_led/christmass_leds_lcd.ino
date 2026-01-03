/* Christmass ugly sweter
 *  - tree LED blinking: LEDs are set on the tips of the 2-story tree
 *  - tree rgb-led tip
 *  - LCD display
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// constants
const int treeLedPins [] = {2, 3, 4, 5, 6, 7, 8};  // output ports at board
const int treeNumPins = 7;
const int randomEntropyPin = 0;
const int ledPin = 12;

void setup() {
  //Setup Tree
  for (int i=0;i<treeNumPins;i++)
    pinMode(treeLedPins[i], OUTPUT);
    
  // initialize the LCD
  lcd.begin();
  pinMode(randomEntropyPin, INPUT);
}

void blinkSeq() {
  for (int i=0;i<treeNumPins;i++) {
    digitalWrite(treeLedPins[i], HIGH);
    delay(100);
    digitalWrite(treeLedPins[i], LOW);
    delay(100);
  } 
}

void blinkPairs() {
  digitalWrite(treeLedPins[0], HIGH);
  delay(1000);
  for (int i=0;i<treeNumPins/2;i++) {
    digitalWrite(treeLedPins[i+1], HIGH);
    digitalWrite(treeLedPins[treeNumPins-i-1], HIGH);
    delay(500);
    digitalWrite(treeLedPins[i+1], LOW);
    
    digitalWrite(treeLedPins[treeNumPins-i-1], LOW);
    delay(500);
  }
  digitalWrite(treeLedPins[0], LOW);
}

void blinkAll() {
  for (int j=0;j<3;j++) {
    for (int i=0;i<treeNumPins;i++) {
      digitalWrite(treeLedPins[i], HIGH);
    }
    delay(500);
    for (int i=0;i<treeNumPins;i++) {
      digitalWrite(treeLedPins[i], LOW);
    }
    delay(500);
  }
}

void slowLcdPrint(String text) {
  for (int i=0; i<text.length(); i++) {
    lcd.print(text.charAt(i));
    delay(200);
  }
}

void printFrame() {
  lcd.home();
  for (int i=0; i<2; i++) {
    lcd.setCursor(0,i*3);
    for (int j=0; j<20; j++) {
      lcd.write('*');
    }
  }
  lcd.setCursor(0,1); lcd.write('*');
  lcd.setCursor(19,1); lcd.write('*');
  lcd.setCursor(0,2); lcd.write('*');
  lcd.setCursor(19,2); lcd.write('*');
}

void delayLcdBlink(int _delay) {
  lcd.cursor();
  lcd.blink();
  // Blinks cursor for specified amount of seconds
  for (int i=_delay; i>0; i--) {
    delay(1000);
  }
  lcd.noBlink();
  lcd.noCursor();
}

void snowAnimation() {
  randomSeed(analogRead(randomEntropyPin));
  lcd.home();
  // Snow falls randomly for some time
  for (int i=0; i<30; i++) {
    int x = random(20);
    lcd.setCursor(x,0);
    for (int j=0; j<4; j++) {
      lcd.setCursor(x,j);
      lcd.print('*');
      delay(100);
    }
  }
  //Cover the entire screen
  for (int i=0; i<4; i++) {
    for (int j=0; j<20; j++) {
      lcd.print('*');
    }
  }
}

void christmasLcd() {
  lcd.clear();
  lcd.backlight();
  printFrame();
  lcd.setCursor(7,1);
  slowLcdPrint("Hello,");
  lcd.setCursor(1,2);
  slowLcdPrint("Malyarevich Family");
  delayLcdBlink(2);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Merry Christmas");
  lcd.setCursor(9,1);
  lcd.print("and");
  lcd.setCursor(3,2);
  lcd.print("Happy New Year!");
  delay(5000);
  lcd.clear();
  lcd.setCursor(6,1);
  lcd.print("HO HO HO");
  delay(1000);
  for (int i=0; i<3; i++) {
    lcd.noBacklight();
    delay(500);
    lcd.backlight();
    delay(1500);
  }
  snowAnimation();
  delay(3000);
  lcd.clear();
  lcd.noBacklight();
}

void loop() {
  blinkSeq();
  blinkPairs();
  delay(500);
  blinkAll();
  christmasLcd();
  delay(1000);
}
