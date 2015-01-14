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

unsigned long i = 0;

void loop()
{
  sinkNode.processMessages();
  
  if(i % 100 == 0)
  {
    sinkNode.discover();
    i = 0;
  }
  
  ++i;

  delay(50);
}


