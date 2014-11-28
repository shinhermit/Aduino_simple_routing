#ifndef SOURCE_NODE_H
#define SOURCE_NODE_H

#include <stdint.h>
#include "Alert.h"

class SourceNode
{
  private:
    uint8_t _myAddress;
    unsigned short _sensorPin;
    
  public:
    SourceNode(const uint8_t & myAddress, const unsigned short & sensorPin);
    
    SourceNode();
    
    void initialize(const uint8_t & myAddress, const unsigned short & sensorPin);
    
    void processMessages()const;
    
    float readSensor()const;
    
    void sendAlert(const Alert & alert)const;
};

#endif

