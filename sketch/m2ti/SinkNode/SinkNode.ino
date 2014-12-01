#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>

#include <SinkNode.h>
#include <CommonValues.h>

SinkNode sinkNode = SinkNode::getInstance();

void setup()
{
  Serial.begin(CommonValues::Routing::XBEE_RATE);
}

void loop()
{
  delay(5000);
  
  sinkNode.processMessages();
  
//  sinkNode.discover();
}

