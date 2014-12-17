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
  static LiquidCrystal_I2C _lcd;

  /// Tells whether the LiquidCristal needs to be initialized or not.
  static bool _initialized;

 public:

  /**
   * Displays the provide string on the LCD screen.
   * \param mess the message which is to be displayed.
   */
  static void display(const String & mess);

  /**
   * Displays the provide string on the LCD screen.
   * \param mess the message which is to be displayed.
   */
  static void display(char * mess);
};

#endif
