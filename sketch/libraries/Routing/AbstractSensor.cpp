#include "AbstractSensor.h"

AbstractSensor::AbstractSensor (int pinNumber, AbstractSensor::SignalType signalType)
{
  _pinNumber = pinNumber;
  _signalType = signalType;
}

AbstractSensor::AbstractSensor (const AbstractSensor & other)
  :_pinNumber(other._pinNumber),
  _signalType(other._signalType)
{}
