#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>
#include <HumiditySensor.h>
#include <SourceNode.h>
#include <CommonValues.h>

const unsigned long myAddress = 0x12345678;

//int pinNumber = 8;

//HumiditySensor humiditySensor(pinNumber);

//SourceNode sourceNode(myAddress, humiditySensor);

//SourceNode sourceNode(myAddress);

//SourceNode sourceNode();

SourceNode sourceNode = SourceNode::getInstance();

void setup()
{
  sourceNode.setAddress(myAddress);
  Serial.begin(CommonValues::Routing::XBEE_RATE);
}

void loop()
{  
  sourceNode.processMessages();
  sourceNode.sendSensorValue();
  //sensorValue = sourceNode.readSensor();
  
  //alert.setSensorValue(sensorValue);
  
  //sourceNode.sendAlert(alert);
  
  delay(5000);
}

