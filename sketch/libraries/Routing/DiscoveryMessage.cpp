#include "DiscoveryMessage.h"

DiscoveryMessage::DiscoveryMessage(const uint8_t & sender, const unsigned short & seqNum,
		 const unsigned short & senderLevel)
  :Message::Message(Message::DISCOVERY, sender, seqNum),
  _senderLevel(senderLevel)
{}

DiscoveryMessage::DiscoveryMessage(const DiscoveryMessage & other)
  :Message::Message(other),
  _senderLevel(other._senderLevel)
{}

DiscoveryMessage & DiscoveryMessage::operator=(const DiscoveryMessage & other)
{
  Message::operator=(other);
  
  _senderLevel = other._senderLevel;
  
  return *this;
}

unsigned short DiscoveryMessage::getSenderLevel()const
{
  return _senderLevel;
}

void DiscoveryMessage::setSenderLevel(const unsigned short & senderLevel)
{
  _senderLevel = senderLevel;
}

