#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include "String.h"

class AbstractSensor {
  public:
  enum SignalType
  {
    DIGITAL,
    ANALOG
  };
  AbstractSensor (const AbstractSensor & other);
  AbstractSensor (int pinNumber, SignalType signalType);
  virtual float readValue () = 0;

  String toString()const;
  
  protected:
  unsigned int _pinNumber;
  SignalType _signalType;
};

#endif
