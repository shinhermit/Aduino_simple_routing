#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

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
  
  protected:
  unsigned int _pinNumber;
  SignalType _signalType;
};

#endif
