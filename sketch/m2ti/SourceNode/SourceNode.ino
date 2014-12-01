#include <XBee.h> // make it added to include path
#include <SoftwareSerial.h>

#include <SourceNode.h>

const uint8_t myAddress = 0x;
int pinNumber = 8;

HumiditySensor humiditySensor(pinNumber);

SourceNode sourceNode(myAddress, humiditySensor);

Alert alert(CommonValues::Alert:DEFAULT_ALERT_TYPE);

float sensorValue = 0.;

void setup()
{
  sourceNode.processMessages();
  
  delay(5000);
}

void loop()
{
  sourceNode.processMessages();
  
  sensorValue = sourceNode.readSensor();
  
  alert.setSensorValue(sensorValue);
  
  sourceNode.sendAlert(alert);
  
  delay(5000);
}

