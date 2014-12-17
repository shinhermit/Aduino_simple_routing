#include "Lcd.h"
#include "CommonValues.h"

Lcd Lcd::_instance;

Lcd::Lcd(const unsigned long & lcdAddr,
	 const unsigned long & nbCols,
	 const unsigned long & nbRows)
  :_lcd(lcdAddr, nbCols, nbRows)
{
  _lcd.init(); 
}

Lcd::Lcd()
   :_lcd(CommonValues::Lcd::LCD_ADDR,
	 CommonValues::Lcd::LCD_NUMBER_OF_COLUMNS,
	 CommonValues::Lcd::LCD_NUMBER_OF_ROWS)
{
  _lcd.init(); 
}

void Lcd::display(const String & mess)
{
  _lcd.print(mess);
}


void Lcd::display(char * mess)
{
  _lcd.print(mess);
}

Lcd & Lcd::getInstance()
{
  return _instance;
}
