#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h> 
#include <Time.h>

#include <SinkNode.h>
#include <CommonValues.h>

SinkNode sinkNode = SinkNode::getInstance();

void setup()
{
  Serial.begin(CommonValues::Routing::XBEE_RATE);
}

void loop()
{
  sinkNode.processMessages();
  
//  sinkNode.discover();

  delay(CommonValues::Routing::SINK_DELAY);
}

