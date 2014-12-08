#include "CommonValues.h"
#include "Message.h"

const unsigned short CommonValues::Alert::DEFAULT_ALERT_TYPE = 1;

const unsigned long CommonValues::Message::MAC_PREFIX = 0x0013A200;

const unsigned long CommonValues::Message::SINK_SUFFIX = 0x40762066;

const unsigned long CommonValues::Message::BROADCAST_PREFIX = 0x00000000;

const unsigned long CommonValues::Message::BROADCAST_SUFFIX = 0x0000FFFF;

const unsigned short CommonValues::Message::SEQUENCE_NUMBER_MOD = 256;

const String CommonValues::Message::Serialization::PREFIX = "/@";

const String CommonValues::Message::Serialization::SEPERATOR = "#";
  
const unsigned short CommonValues::Routing::SENSOR_VALUES_MAX_BUFFER = 5;

const unsigned int CommonValues::Routing::XBEE_RATE = 38400;

const unsigned short CommonValues::Routing::SINK_LEVEL = 0;

const unsigned short CommonValues::Routing::SINK_DELAY = 4000;

const unsigned short CommonValues::Routing::SOURCE_DELAY = 5000;
