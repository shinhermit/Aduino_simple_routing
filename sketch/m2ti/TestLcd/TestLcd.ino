#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>

#include <Lcd.h>
#include <CommonValues.h>

void setup()
{
  Lcd & lcd = Lcd::getInstance(); // TODO: problem when instanciating as a global variable
  
  // Activate scrolling
  lcd.setScrollingOn(true);
  
  lcd.display("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); // ABCDEFGHIJKLMNOP
  
  delay(2000);
  lcd.update(); // QRSTUVWXYZ
  
//  delay(2000);
//  lcd.update(); // ABCDEFGHIJKLMNOP
  
//  delay(2000);
//  lcd.update(); // QRSTUVWXYZ
  
//  delay(2000);
//  lcd.update(); // ABCDEFGHIJKLMNOP
}

void loop()
{
  //lcd.scroll();
}
