#ifndef SOURCE_NODE_H
#define SOURCE_NODE_H

#include <stdint.h>
#include <Alert.h>
#include <AbstractSensor.h>
#include <MessageHistory.h>
#include <XBee.h>
#include <DiscoveryMessage.h>
#include <Message.h>

class SourceNode
{
  private:
    uint8_t _myAddress;
    AbstractSensor * _sensor;
    unsigned short _alertSequenceNumber;
    Rx16Response _rx16;
    Rx64Response _rx64;
    XBee _xbee;
    MessageHistory _history;
    unsigned short _level;
    unsigned short _lastDiscoverySequence;
    unsigned short _lastAlertSequence;
    bool _firstDiscovery;

    unsigned short _getAlertSequenceNumber();
    void _sendString(const String & message);
    String receiveMessage();
    
  public:
    SourceNode(const uint8_t & myAddress, AbstractSensor & sensor);
    
    SourceNode();
    
    void initialize(const uint8_t & myAddress, AbstractSensor & sensor);
    
    void processMessages();
    
    float readSensor()const;
    
    void forwardAlert(const Alert & alert);

    void sendAlert(const Alert & alert);
    void sendDiscovery(const DiscoveryMessage & discoveryMessage);
    void sendMessage(const Message & message);

};

#endif


