/*
 * NOTE: One need to include <XBee.h> in the sketch main file
 * in order to make the latter library added to the include path.
 */

#ifndef SINK_NODE_H
#define SINK_NODE_H

#include <stdint.h>

#include <Arduino.h>

#include <XBee.h>

#include "DiscoveryMessage.h"
#include "MessageHistory.h"
#include "String.h"

class SinkNode
{
  private:
    unsigned short _seqNum;
    MessageHistory _history;
    
    XBee _xbee;
    
    Rx16Response _rx16;
    Rx64Response _rx64;
    
    static SinkNode _instance;
    
    void initialize();
    
    SinkNode();
    
    void broadcastMessage(const DiscoveryMessage & mess);
    
    String receiveMessage();
    
    bool isNew(const Message & mess)const;
    
  public:
    SinkNode(const SinkNode & other);
    
    static SinkNode & getInstance();
    
    void processMessages();
    
    void discover();
};

#endif

