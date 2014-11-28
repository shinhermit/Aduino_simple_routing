#include "SourceNode.h"

uint8_t nodeAddress;
unsigned short sensorPin;
SourceNode sourceNode;
float sensorValue, criticalMinValue, criticalMaxValue;
unsigned short sensorType;

void setup()
{
  // Setup the node
  nodeAddress = 0x00000000;
  sensorPin = 5;
  sourceNode.initialize(nodeAddress, sensorPin);
  
  // Sensor/alerts parameters
  sensorType = 1;
  criticalMinValue = 5.f;
  criticalMaxValue = 10.f;
}

void loop()
{
  sourceNode.processMessages();
  
  sensorValue = sourceNode.readSensor();
  
  if(sensorValue < criticalMinValue || sensorValue > criticalMaxValue)
  {
    sourceNode.sendAlert(Alert(sensorType, sensorValue));
  }
  
  delay(5000);
}
