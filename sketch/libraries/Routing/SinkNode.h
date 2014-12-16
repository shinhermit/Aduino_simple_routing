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

/**
 * The sink node of the simple routing protocol.
 * <p>Reminder: in the simple routing protocol, the sink node regularly sends discovery messages to other nodes. The other nodes can send alerts to the sink node.</p>
 * <p>The discovery messages allows to built the routes in the arduino network. The algorithm works as follow:
 * <ol>
 * <li>The sink node boradcasts a discovery message, containing it's address and the level 0.</li>
 * <li>Each node which receives this discovery sets his own level to 0+1, adds the sender to it's routing table and braodcasts a discovery with it's address and it's updated level.</li>
 * <li>And so on, until the algorithm stops.</li>
 * </ol>
 * </p>
 * <p>In order that the algorithm stops, it is necessary that a node which has already set it's level does not updates this level again in the same discovery session, neither should it broadcast again any discovery message.</p>
 * <p>The sink node must also be awareof not treating many time the message alert message, possibly caused by multiple forwarding.</p>
 */
class SinkNode
{
  private:
    /// The current sequence number of the discovery messages.
    unsigned short _seqNum;
    /// The message history manager.
    MessageHistory _history;
    
    /// The XBee object, which allows to send and receive packets via the XBee board.
    XBee _xbee;
    
    /// The 16 bit response object.
    Rx16Response _rx16;
    /// The 64 bit response object.
    Rx64Response _rx64;
    
    /// The singleton instance of the sink node.
    static SinkNode _instance;
    
    /// Initializes the sink node. Useful because multiple constructors.
    void initialize();

    /// Creates a sink node.
    SinkNode();
    
    /**
     * Broadcasts a discovery message.
     * \param mess the Message which is to be broadcasted.
     */
    void broadcastMessage(const DiscoveryMessage & mess);
    
    /**
     * Fetches a message from the reception queue.
     * \param the fetched message.
     */
    String receiveMessage();
    
    /**
     * Processes a unique message from the receive buffer.
     * \return true if a message was available, false otherwise.
     */
    bool processNextMessage();
    
  public:
    /**
     * Copy constructor.
     */
    SinkNode(const SinkNode & other); // TODO: remove (because singleton).
   
    /**
     * Provides the singleton instance of the sink node.
     * \return the singleton instance of the sink node.
     */ 
    static SinkNode & getInstance();
    
    /**
     * Treats the messages in the xbee queue.
     */
    void processMessages();
    
    /**
     * Broadcasts discovery messages.
     */
    void discover();
};

#endif

