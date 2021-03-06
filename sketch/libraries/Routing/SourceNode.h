/*
 * NOTE: One need to include <XBee.h> in the sketch main file
 * in order to make the latter library added to the include path.
 */

#ifndef SOURCE_NODE_H
#define SOURCE_NODE_H

#include <Arduino.h>

#include <XBee.h>

#include "DiscoveryMessage.h"
#include "MessageHistory.h"

class SourceNode
{
  private:
	bool _broadcast;
    unsigned short _seqNum;
    unsigned short _lastAlertSequenceNumber;
    unsigned short _lastDiscoverySequence;
	unsigned long _lastAlertTimestamp;
    unsigned short _level;
	unsigned long _myAddress;
	unsigned long _firstGatewayToSink;
	unsigned long _lastGatewayToSink;

    MessageHistory _history;
    
    XBee _xbee;
    
    Rx16Response _rx16;
    Rx64Response _rx64;
    
    static SourceNode _instance;
    
    void initialize();
    
    SourceNode();
    
    String receiveMessage();
	void send(const Message & mess);
	void sendMessage(XBeeAddress64 & addr, const Message & mess);
	void broadcastMessage(const Message & mess);
	void unicastMessageToSink(const Message & mess);
	unsigned short getSequenceNumber();
	bool isNewSequenceNumber(const unsigned short & sequenceNumber) const;
	bool firstIsNewDiscoverySequence(const unsigned short a, const unsigned short b) const;

  public:
    SourceNode(const SourceNode & other);
    
    static SourceNode & getInstance();
    
	void setAddress();
    
	bool processMessage();
    void processMessages();

	void sendSensorValue();
};

#endif

