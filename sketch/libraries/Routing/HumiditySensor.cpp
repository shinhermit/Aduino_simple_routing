#include "HumiditySensor.h"


#include <Arduino.h>

HumiditySensor::HumiditySensor(int pinNumber)
  :AbstractSensor::AbstractSensor(pinNumber, AbstractSensor::ANALOG)
{}


float HumiditySensor::readValue()
{
  int sensorValue = analogRead(_pinNumber);
  
  return sensorValue * 3.3 /1024.0;
}

