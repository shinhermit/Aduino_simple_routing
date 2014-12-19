#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>

#include <Lcd.h>

void setup()
{
  Lcd & lcd = Lcd::getInstance();
  
  //delay(1000);
  lcd.display("Hello ");
  lcd.display("Bye");
  
  // Activate scrolling
  lcd.setScrollingOn(true);
  
  lcd.display("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  delay(1000);
  lcd.update();
  delay(1000);
  lcd.update();
  delay(1000);
  lcd.update();
  delay(1000);
  lcd.update();
}

void loop()
{
}
