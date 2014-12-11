#ifndef DISCOVERY_MESSAGE_H
#define DISCOVERY_MESSAGE_H

#include "Message.h"

/**
 * A Message which carries a path discovery informations.
 * <p>Reminder: the simple routing protocol implemented by this
 * application is proactive an hierarchical (with the concept of levels, abstraction of distance from the sink node).</p>
 */
class DiscoveryMessage : public Message
{
 private:
  /**
   * The level of the node which was the last to forward the discovery message.
   */
  unsigned short _senderLevel;

 protected:
  /**
   * \overload
   */
  virtual String _getSpecialString()const;

 public:
  /**
   * Creates a Message which carries path discovery information.
   * \param sender the suffix of the address of the node which was the last to forward the discovery message.
   * \param seqNum the sequence number of the discovery session (not of the message).
   * \param senderLevel the level of the node which was the last to forward the discovery message.
   */
  DiscoveryMessage(const unsigned long & sender, const unsigned short & seqNum,
		 const unsigned short & senderLevel);

  /**
   * Copy constructor.
   */
  DiscoveryMessage(const DiscoveryMessage & other);
  
  /**
   * Operator =
   */
  DiscoveryMessage & operator=(const DiscoveryMessage & other);

  /**
   * Provides the routing level of the node which was the last to forward the discovery message.
   * \return the routing level the node which was the last to forward the discovery message.
   */
  unsigned short getSenderLevel()const;

  /**
   * Defines the routing level of the node which is the last to forward the discovery message.
   * \param senderLevel the routing level of the node which is the last to forward the discovery message.
   */
  void setSenderLevel(const unsigned short & senderLevel);
};

#endif

