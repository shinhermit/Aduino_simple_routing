#include "DiscoveryMessage.h"

DiscoveryMessage::DiscoveryMessage(const unsigned long & sender, const unsigned short & seqNum,
		 const unsigned short & senderLevel)
  :Message::Message(Message::DISCOVERY, sender, seqNum, senderLevel)
{}

DiscoveryMessage::DiscoveryMessage(const DiscoveryMessage & other)
  :Message::Message(other)
{}

DiscoveryMessage & DiscoveryMessage::operator=(const DiscoveryMessage & other)
{
  Message::operator=(other);
  
  return *this;
}

