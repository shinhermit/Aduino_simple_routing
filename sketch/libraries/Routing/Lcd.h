#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/**
* Wrapper for the LiquidCristal librairy.
*/
class Lcd
{
 private:
  /// instance of the LiquidCristal librairy object. 
  LiquidCrystal_I2C _lcd;

  /**
   * Creates an object which can display to an LCD screen.
   * \param lcdAddr the address of the LCD device.
   * \param nbCols the number of columns of the LCD screen.
   * \param nbRows the number of rows of the LCD screen.
   */
  Lcd(const unsigned long & lcdAddr,
      const unsigned long & nbCols,
      const unsigned long & nbRows);

  /**
   * Creates an object which can display to an LCD screen.
   */
  Lcd();

  /// The singleton instance of this LCD printer class.
  static Lcd _instance;

 public:
  /**
   * Procides the singleton instance of this LCD printer class.
   * \return the singleton instance of this LCD printer class.
   */
  static Lcd & getInstance();

  /**
   * Display the provide string on the LCD screen.
   * \param mess the message which is to be displayed.
   */
  void display(const String & mess);

  /**
   * Display the provide string on the LCD screen.
   * \param mess the message which is to be displayed.
   */
  void display(char * mess);
};

#endif
