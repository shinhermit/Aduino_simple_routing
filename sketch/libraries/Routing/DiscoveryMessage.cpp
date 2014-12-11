#include "DiscoveryMessage.h"

DiscoveryMessage::DiscoveryMessage(const unsigned long & sender, const unsigned short & seqNum,
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

String DiscoveryMessage::_getSpecialString()const
{
  return String("\tSender level: ")+_senderLevel+String("\n");
}
