#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>

#include <Lcd.h>

void setup()
{
  Lcd::display("Hello ");
  Lcd::display("Bye");
}

void loop()
{
}
