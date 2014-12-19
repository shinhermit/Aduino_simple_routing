#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>

#include <Lcd.h>

Lcd & lcd = Lcd::getInstance();
  
void setup()
{
  
  //delay(1000);
  lcd.display("Hello ");
  lcd.display("Bye");
  
  // Activate scrolling
  lcd.setScrollingOn(true);
  lcd.display("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); // ABCDEFGHIJKLMNOP
}

bool first = true;

void loop()
{
  lcd.block(1000);
  lcd.update(); // QRSTUVWXYZ
  
  if( !lcd.isBlocked() )
  {
    if(first)
    {
      lcd.display("ZYXVUTSRQPONMLKJIHGFEDCBA"); // ZYXVUTSRQPONMLKJ
      first = false;
    }
    
    lcd.block();
    lcd.update(); // Should do nothing
    lcd.unblock();
    lcd.update();  // IHGFEDCBA
  }
  
}
