#ifndef COMMON_VALUES_H
#define COMMON_VALUES_H

#include <stdint.h>

#include <Arduino.h>
#include <XBee.h>

#include "String.h"

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
      static const uint8_t MAC_PREFIX;
      /// The suffix of the MAC address if the sink node.
      static const uint8_t SINK_SUFFIX;
      /// The prefix of the MAC broadcast address.
      static const uint8_t BROADCAST_PREFIX;
      /// The suffix of the MAC broadcast address.
      static const uint8_t BROADCAST_SUFFIX;
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
      /// The time the sinl node waits before sending messages.
      static const unsigned short SINK_DELAY;
      /// The time the source nodes wait before sending messages.
      static const unsigned short SOURCE_DELAY;
  };
}

#endif

