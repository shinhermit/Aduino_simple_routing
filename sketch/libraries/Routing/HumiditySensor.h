#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include "AbstractSensor.h"

class HumiditySensor : public AbstractSensor {  
  private:

  public:
  HumiditySensor(int pinNumber);
  float readValue();  
};

#endif
