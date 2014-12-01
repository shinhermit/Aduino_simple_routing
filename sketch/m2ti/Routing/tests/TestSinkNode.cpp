#include "SinkNode.h"

SinkNode sinkNode = SinkNode.getInstance();

void setup()
{
}

void loop()
{
  sinkNode.processMessages();
  
  sinkNode.discover();
  
  delay(5000);
}
