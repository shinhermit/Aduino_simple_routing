#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>

#include <SinkNode.h>


SinkNode sinkNode = SinkNode::getInstance();

void setup()
{
  sinkNode.processMessages();
  
  sinkNode.discover();
  
  delay(5000);
}

void loop()
{
//  sinkNode.processMessages();
  
//  sinkNode.discover();
  
//  delay(5000);
}

