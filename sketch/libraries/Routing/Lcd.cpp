#include "Lcd.h"
#include "CommonValues.h"

#include <SoftwareSerial.h>

Lcd * Lcd::_instance = NULL;

Lcd::Lcd(const unsigned long & lcdAddr,
	 const unsigned long & nbCols,
	 const unsigned long & nbRows)
  :_lcd(lcdAddr, nbCols, nbRows),
   _maxLen(nbRows *nbCols),
   _scrollingOn(false),
   _mess(),
   _inputCursor(0)
{
  _lcd.init(); 
  _lcd.backlight();
  _lcd.clear();
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
  if(_scrollingOn
     && mess.length() > _maxLen)
  {
    _mess = mess;
    _inputCursor = 0;

    _displayScrolled(mess);
  }
  else
  {
    _lcd.print(mess);
  }
}

void Lcd::display(char * mess)
{
  display(String(mess));
}

void Lcd::scroll()
{
  block(CommonValues::Lcd::LCD_REFRESH_PERIOD);
  update();
}

void Lcd::onUpdate()
{
  if(_scrollingOn)
  {
    _displayScrolled(_mess);
  }
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

void Lcd::setScrollingOn(bool on)
{
  _scrollingOn = on;
}

bool Lcd::isScrollingOn()const
{
  return _scrollingOn;
}

void Lcd::_displayScrolled(const String & mess)
{
  _lcd.clear();

  if(mess.length() <= _maxLen)
  {
    display(mess);
  }
  else
  {
    if(_inputCursor <= mess.length() - 1)
    {
      unsigned long nbChars = mess.length() - _inputCursor;
      unsigned long start = _inputCursor;
      unsigned long end;

      if(nbChars <= _maxLen)
      {
	end = mess.length();
      }
      else
      {
	end = _inputCursor + _maxLen;
      }

      display(mess.substring(start, end));

      _inputCursor = _inputCursor + _maxLen;
      if( _inputCursor > mess.length() )
      {
	_inputCursor = 0;
      }
    }
  }
}
