#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <XBee.h> // make it added to include path
 
#include <Lcd.h>
#include <CommonValues.h>

Lcd * l;

void setup()
{
  Lcd & lcd = Lcd::getInstance(); // TODO: problem when instanciating as a global variable
  l = &lcd;
  
  // Activate scrolling
  lcd.setScrollingOn(true);
  
  lcd.display("La sottise, l'erreur, le peche, la lesine, occupent nos esprits et travaillent nos corps, et nous alimentons nos aimables remords, comme les mendiants nourrissent leur vermine.");
  
//  delay(3000);
//  lcd.update();
  
//  delay(3000);
//  lcd.update();
  
//  delay(3000);
//  lcd.update();
  
//  delay(3000);
//  lcd.update();
  
//  delay(3000);
//  lcd.update();
  
//  delay(3000);
//  lcd.update();
  
//  delay(3000);
//  lcd.update();
}

void loop()
{
  l->scroll();
}
