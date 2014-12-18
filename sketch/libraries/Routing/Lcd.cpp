#include "Lcd.h"
#include "CommonValues.h"

Lcd * Lcd::_instance = NULL;

Lcd::Lcd(const unsigned long & lcdAddr,
	 const unsigned long & nbCols,
	 const unsigned long & nbRows)
  :_lcd(lcdAddr, nbCols, nbRows)
{
  _lcd.init(); 
  _lcd.backlight();
}

Lcd::~Lcd()
{
  if(Lcd::_instance != NULL)
  {
    delete Lcd::_instance;
  }
}

void Lcd::display(const String & mess)
{
  _lcd.print(mess);
}


void Lcd::display(char * mess)
{
  _lcd.print(mess);
}

Lcd & Lcd::getInstance(const unsigned long & lcdAddr,
		       const unsigned long & nbCols,
		       const unsigned long & nbRows)
{
  if(Lcd::_instance == NULL)
  {
    Lcd::_instance = new Lcd(lcdAddr, nbCols, nbRows);
  }

  return *Lcd::_instance;
}

Lcd & Lcd::getInstance()
{
  return 
    Lcd::getInstance(CommonValues::Lcd::LCD_ADDR,
		     CommonValues::Lcd::LCD_NUMBER_OF_COLUMNS,
		     CommonValues::Lcd::LCD_NUMBER_OF_ROWS);
}
