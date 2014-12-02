#ifndef COMMON_VALUES_H
#define COMMON_VALUES_H

#include <stdint.h>

#include <Arduino.h>
#include <XBee.h>

#include "String.h"

namespace CommonValues
{
  class Alert
  {
    public:
      static const unsigned short DEFAULT_ALERT_TYPE;
  };
  
  class Message
  {
    public:
     struct Address64
     {
       Address64();
       Address64(uint8_t prefix, uint8_t suffix);

       uint8_t prefix;
       uint8_t suffix;
     };

      static const uint8_t MAC_PREFIX;
      static const uint8_t SINK_SUFFIX;
      static const uint8_t BROADCAST_PREFIX;
      static const uint8_t BROADCAST_SUFFIX;
      static const unsigned short SEQUENCE_NUMBER_MOD;
    
    class Serialization
    {
      public:
        static const String PREFIX;
        static const String SEPERATOR;    
    };
  };
  
  class Routing
  {
    public:
      static const unsigned short SENSOR_VALUES_MAX_BUFFER;
      static const unsigned int XBEE_RATE;
      static const unsigned short SINK_LEVEL;
      static const unsigned short SINK_DELAY;
      static const unsigned short SOURCE_DELAY;
  };
}

#endif

