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

const unsigned short CommonValues::Routing::SINK_DELAY = 50;

const unsigned short CommonValues::Routing::SOURCE_DELAY = 5000;

const unsigned short CommonValues::Routing::SOURCE_WAKEUP_DELAY = 500;

const unsigned short CommonValues::Routing::MAX_PEERS = 10;

const unsigned long CommonValues::Routing::DELAY_LIMIT =
  CommonValues::Routing::SOURCE_DELAY * CommonValues::Routing::MAX_PEERS;

const unsigned long CommonValues::Lcd::LCD_ADDR = 0x20;

const unsigned long CommonValues::Lcd::LCD_NUMBER_OF_COLUMNS = 16;

const unsigned long CommonValues::Lcd::LCD_NUMBER_OF_ROWS = 2;
