#ifndef M2TI_UTILITY_H
#define M2TI_UTILITY_H

#include <Arduino.h>

#include <XBee.h>
#include <String.h>

/**
 * Utility class for XBee functionalities.
 */
namespace Utility
{
  class Board
  {
  public:
    static String getMACLowPart(XBee & xbee);

    static String getMACHighPart(XBee & xbee);

    static String getMACAddress(XBee & xbee);

  private:
    static String getMACPart(XBee & xbee, uint8_t cmd[]);

    static int sendAtCommand(XBee & xbee,
		      AtCommandRequest & atRequest,
		      AtCommandResponse & atResponse);
  };

  class Convert
  {
  public:
    static float stringToFloat(String value);

    static String floatToString(float value);
  };
}

#endif

