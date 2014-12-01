#ifndef SOURCE_NODE_H
#define SOURCE_NODE_H

#include <stdint.h>
#include "Alert.h"
#include "AbstractSensor.h"
#include <../XBee/XBee.h>

class SourceNode
{
  private:
    uint8_t _myAddress;
    AbstractSensor * _sensor;
    unsigned short _alertSequenceNumber;
    unsigned short _getAlertSequenceNumber();
    XBee _xbee;
    void _sendString(const String message);
    
  public:
    SourceNode(const uint8_t & myAddress, AbstractSensor & sensor);
    
    SourceNode();
    
    void initialize(const uint8_t & myAddress, AbstractSensor & sensor);
    
    void processMessages()const;
    
    float readSensor()const;
    
    void sendAlert(const Alert & alert);

};

#endif


