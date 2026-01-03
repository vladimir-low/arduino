/*
 * he I2C connections are on SDA=A4 and SCL=A5
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const int randomEntropyPin = 0;
const int ledPin = 12;

void setup() {
  // initialize the LCD
  lcd.begin();
  // Set ports
  pinMode(randomEntropyPin, INPUT);
//  for (int i=1)
  pinMode(ledPin, OUTPUT);
}

void delayBlink(int _delay) {
  lcd.cursor();
  lcd.blink();
  // Blinks cursor for specified amount of seconds
  for (int i=_delay; i>0; i--) {
    delay(1000);
  }
  lcd.noBlink();
  lcd.noCursor();
}

void slowPrint(String text) {
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

void flashLed() {
  for (int i=0; i<5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}

void loop() {
  flashLed();
  lcd.clear();
  lcd.backlight();
  printFrame();
  lcd.setCursor(7,1);
  slowPrint("Hello,");
  lcd.setCursor(1,2);
  lcd.print("Malyarevich Family");
  delayBlink(5);
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
      for (int i=0; i<3; i++) {
    lcd.noBacklight();
    delay(500);
    lcd.backlight();
    delay(1500);
  }
  flashLed();
  snowAnimation();
  delay(3000);
  lcd.clear();
  lcd.noBacklight();
  delay(5000);

}
