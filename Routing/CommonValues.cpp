#include "CommonValues.h"
#include "Message.h"

const unsigned short CommonValues::Alert::DEFAULT_ALERT_TYPE = 1;

const uint8_t CommonValues::Message::MAC_PREFIX = 0x0013A200;

const uint8_t CommonValues::Message::SINK_SUFFIX = 0x40762066;

//const XBeeAddress64 CommonValues::Message::SINK_ADDRESS = XBeeAddress64(0x0013A200, 0x40762066);

//const XBeeAddress64 CommonValues::Message::BROADCAST_ADDRESS = XBeeAddress64(0x00000000, 0x0000FFFF);

const String CommonValues::Message::Serialization::PREFIX = "/@";

const String CommonValues::Message::Serialization::SEPERATOR = "#";
  
const unsigned short CommonValues::Routing::SENSOR_VALUES_MAX_BUFFER = 5;

const int CommonValues::Routing::XBEE_RATE = 38400;

const unsigned short CommonValues::Routing::SINK_LEVEL = 0;

