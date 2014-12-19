#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Blockable.h>

/**
* Wrapper for the LiquidCristal librairy.
*/
class Lcd : public Blockable
{
 private:
  /// instance of the LiquidCristal librairy object. 
  LiquidCrystal_I2C _lcd;

  /// The maximum number of characters that can be displayed on the LCD.
  const unsigned long _maxLen;

  /// A flag which tells whether the scrolling is activated or not.
  bool _scrollingOn;

  /// The message which is to be scrolled displayed.
  String _mess;

  /// A cursor which indicates where the display should begin in the target string.
  unsigned long _inputCursor;

  /// The singleton instance of this LCD printer class.
  static Lcd * _instance;

  /**
   * Displays the appropriate number of characters from the string and places the input cursor at the position where the next display should begin.
   * \param mess the message which is to be displayed.
   */
  void _displayScrolled(const String & mess);

  /**
   * Creates an object which can display to an LCD screen.
   * \param lcdAddr the address of the LCD device.
   * \param nbCols the number of columns of the LCD screen.
   * \param nbRows the number of rows of the LCD screen.
   */
  Lcd(const unsigned long & lcdAddr,
      const unsigned long & nbCols,
      const unsigned long & nbRows);

 protected:

  /**
   * \overload
   */
  virtual void onUpdate();


 public:
  /**
   * Procides the singleton instance of this LCD printer class.
   * \return the singleton instance of this LCD printer class.
   */
  static Lcd & getInstance(const unsigned long & lcdAddr,
			   const unsigned long & nbCols,
			   const unsigned long & nbRows);

  /**
   * Destructor.
   */
  ~Lcd();

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

  /**
   *Scrolls down the text on the display.
   */
  void scroll();

  /**
   * Defines whether long texts should be scrolled or not.
   * \param on true to activate scrolling, false otherwise.
   */
  void setScrollingOn(bool on);

  /**
   * Tells whether scrolling the long texts is activated or not.
   * \return true if scrolling is activated, false otherwise.
   */
  bool isScrollingOn()const;
};

#endif
