#ifndef DISCOVERY_MESSAGE_H
#define DISCOVERY_MESSAGE_H

#include "Message.h"

class DiscoveryMessage : public Message
{
 private:
  unsigned short _senderLevel;

 public:
  DiscoveryMessage(const unsigned long & sender, const unsigned short & seqNum,
		 const unsigned short & senderLevel);

  DiscoveryMessage(const DiscoveryMessage & other);
  
  DiscoveryMessage & operator=(const DiscoveryMessage & other);

  unsigned short getSenderLevel()const;

  void setSenderLevel(const unsigned short & senderLevel);
};

#endif

