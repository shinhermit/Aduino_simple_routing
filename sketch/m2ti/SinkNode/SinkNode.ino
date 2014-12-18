#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>
#include <CommonValues.h>

#include <Lcd.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <SinkNode.h>

SinkNode sinkNode = SinkNode::getInstance();

void setup()
{
  Serial.begin(CommonValues::Routing::XBEE_RATE);
}

void loop()
{
  sinkNode.processMessages();
  
  sinkNode.discover();

  delay(5000);
//  delay(CommonValues::Routing::SINK_DELAY);
}

