#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  // initialize the LCD
  lcd.begin();
}


void loop() {
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(7,1);
  lcd.print("Hello, world!");
  delay(5000);
  lcd.noBacklight();
  delay(3000);
}
