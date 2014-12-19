#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>
#include <HumiditySensor.h>
#include <SourceNode.h>
#include <CommonValues.h>
#include <Lcd.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

const unsigned long myAddress = 0x40922070;

//int pinNumber = 8;

//HumiditySensor humiditySensor(pinNumber);

//SourceNode sourceNode(myAddress, humiditySensor);

//SourceNode sourceNode(myAddress);

//SourceNode sourceNode();

SourceNode sourceNode = SourceNode::getInstance();


void setup()
{
  Serial.begin(38400);
  sourceNode.setAddress(myAddress);
//  Lcd::getInstance().display("test");
}

void loop()
{  
  
  sourceNode.processMessages();
  
  sourceNode.sendSensorValue();
  
  delay(CommonValues::Routing::SOURCE_WAKEUP_DELAY);
  //delay(50);
}

