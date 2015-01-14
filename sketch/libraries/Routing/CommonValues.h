#ifndef COMMON_VALUES_H
#define COMMON_VALUES_H

#include <Arduino.h>
#include <XBee.h>

/**
 * Holds the constants of the application.
 */
namespace CommonValues
{
  /**
   * Constants used by alerts.
   */
  class Alert
  {
    public:
      /// The default type messages.
      static const unsigned short DEFAULT_ALERT_TYPE;
  };
  
  /**
   * Constants used by messages.
   */
  class Message
  {
    public:
      /// The prefix of the MAC addresses.
      static const unsigned long MAC_PREFIX;

      /// The suffix of the MAC address if the sink node.
      static const unsigned long SINK_SUFFIX;

      /// The prefix of the MAC broadcast address.
      static const unsigned long BROADCAST_PREFIX;

      /// The suffix of the MAC broadcast address.
      static const unsigned long BROADCAST_SUFFIX;

      /// The number which is to be used as the limit of the sequence numbers.
      static const unsigned short SEQUENCE_NUMBER_MOD;
    
  
  /**
   * Constants used in serialization.
   */
    class Serialization
    {
      public:
        /// The string added at the beginning of the serialized messages.
        static const String PREFIX;

	/// The seperator of the fields of a serialized message.
        static const String SEPERATOR;    
    };
  };
  
  /**
   * Constants used in the routing.
   */
  class Routing
  {
    public:
      /// The max size of buffer which keeps the values read from the sensors.
      static const unsigned short SENSOR_VALUES_MAX_BUFFER;

      /// The transmission rate of the XBee object.
      static const unsigned int XBEE_RATE;

      /// The value of the level of the sink node.
      static const unsigned short SINK_LEVEL;

      /// The time the sink node waits before sending messages.
      static const unsigned short SINK_DELAY;

	  /// Delay between two source node wakeups
	  static const unsigned short SOURCE_WAKEUP_DELAY;

      /// The minimum time between two alerts.
      static const unsigned short SOURCE_DELAY;

      /// The maximum numbers for peers in the arduino network (estimation).
      static const unsigned short MAX_PEERS;

	  /// The maximum number of loss, after which a sequence number is not treated as a reset but as representing a duplicate.
	  static const unsigned short MAX_LOSS_TOLERANCE;

      /// The maximum delay (in seconds) between 2 messages after which we consider that the new messsage can not be a duplication of the first one (it is thus considered that a lot of messages where lost).
      static const unsigned long DELAY_LIMIT;
  };

  /**
   * Constants used for the LCD display.
   */
  class Lcd
  {
  public:
    /// The default address of the LCD device
    static const unsigned long LCD_ADDR;

    /// The default number of columns of the LCD screen
    static const unsigned long LCD_NUMBER_OF_COLUMNS;

    /// The default number of rows of the LCD screen
    static const unsigned long LCD_NUMBER_OF_ROWS;

    /// The time interval after which the LCD refreshes it's display (scrolls the text).
    static const unsigned long LCD_REFRESH_PERIOD;
  };
}

#endif

