#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>
#include <HumiditySensor.h>
#include <SourceNode.h>
#include <CommonValues.h>
const uint8_t myAddress = 0x12345678;
int pinNumber = 8;

HumiditySensor humiditySensor(pinNumber);

SourceNode sourceNode(myAddress, humiditySensor);

Alert alert(CommonValues::Alert::DEFAULT_ALERT_TYPE);

float sensorValue = 0.;

void setup()
{
  Serial.begin(CommonValues::Routing::XBEE_RATE);
}

void loop()
{
  //sourceNode.processMessages();
  
  sensorValue = sourceNode.readSensor();
  
  alert.setSensorValue(sensorValue);
  
  sourceNode.sendAlert(alert);
  
  delay(5000);
}

