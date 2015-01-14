#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>
#include <HumiditySensor.h>
#include <SourceNode.h>
#include <CommonValues.h>
#include <Lcd.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

const unsigned long myAddress = 0x4076205E;

//int pinNumber = 8;

//HumiditySensor humiditySensor(pinNumber);

//SourceNode sourceNode(myAddress, humiditySensor);

SourceNode sourceNode = SourceNode::getInstance();

Lcd * lcd;
void setup()
{
  Serial.begin(38400);
  sourceNode.setAddress();
  lcd = Lcd::getInstance();
  
  //lcd->setScrollingOn(true);
}

void loop()
{  
  
  sourceNode.processMessages();
  
  sourceNode.sendSensorValue();
  
  //lcd->scroll();
  
  delay(CommonValues::Routing::SOURCE_WAKEUP_DELAY);
}

