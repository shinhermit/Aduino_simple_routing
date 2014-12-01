#include "CommonValues.h"
#include "Message.h"

const unsigned short CommonValues::Alert::DEFAULT_ALERT_TYPE = 1;

const uint8_t CommonValues::Message::MAC_PREFIX = 0x0013A200;

const uint8_t CommonValues::Message::SINK_SUFFIX = 0x40762066;

const CommonValues::Message::Address64 CommonValues::Message::SinkAddress(0x0013A200, 0x40762066);
const CommonValues::Message::Address64 CommonValues::Message::BroadcastAddress(0x00000000, 0x0000FFFF);

const String CommonValues::Message::Serialization::PREFIX = "/@";

const String CommonValues::Message::Serialization::SEPERATOR = "#";
  
const unsigned short CommonValues::Routing::SENSOR_VALUES_MAX_BUFFER = 5;

const unsigned int CommonValues::Routing::XBEE_RATE = 38400;

const unsigned short CommonValues::Routing::SINK_LEVEL = 0;


CommonValues::Message::Address64::Address64()
  :prefix(0),
   suffix(0)
{}

CommonValues::Message::Address64::Address64(uint8_t pref, uint8_t suf)
  :prefix(pref),
   suffix(suf)
{}
