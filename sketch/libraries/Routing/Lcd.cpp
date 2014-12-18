#include "Lcd.h"
#include "CommonValues.h"

LiquidCrystal_I2C Lcd::_lcd(CommonValues::Lcd::LCD_ADDR,
			    CommonValues::Lcd::LCD_NUMBER_OF_COLUMNS,
			    CommonValues::Lcd::LCD_NUMBER_OF_ROWS);

bool Lcd::_initialized = false;

void Lcd::display(const String & mess)
{
  if(!_initialized)
  {
    _lcd.init();

    _lcd.backlight();
    _initialized = true;
  }
    
  _lcd.print(mess);
}


void Lcd::display(char * mess)
{
  if(!_initialized)
  {
    _lcd.init();

    _lcd.backlight();
    _initialized = true;
  }

  _lcd.print(mess);
}
