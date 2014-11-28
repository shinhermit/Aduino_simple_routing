#ifndef COMMON_VALUES_H
#define COMMON_VALUES_H

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
      static const uint8_t MAC_PREFIX;
      static const uint8_t SINK_SUFFIX;
      //static const XBeeAddress64 SINK_ADDRESS;
      //static const XBeeAddress64 BROADCAST_ADDRESS;
    
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
      static const int XBEE_RATE;
      static const unsigned short SINK_LEVEL;
  };
}

#endif

