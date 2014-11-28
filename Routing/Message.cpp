#include "Message.h"

const Message::MessageType Message::DEFAULT_TYPE = Message::ALERT;

Message::Message(const Message::MessageType & type, const uint8_t & sender,
		 const unsigned short & seqNum)
  :_messageType(type),
  _sender(sender),
  _seqNum(seqNum)
{}

Message::Message(const uint8_t & sender, const unsigned short & seqNum)
  :_messageType(Message::DEFAULT_TYPE),
  _sender(sender),
  _seqNum(seqNum)
{}

Message::Message(const Message & other)
  :_messageType(other._messageType),
  _sender(other._sender),
  _seqNum(other._seqNum)
{}
  
Message::Message()
  :_messageType(Message::DEFAULT_TYPE),
  _sender(0),
  _seqNum(0)
{}

Message::Message & Message::operator=(const Message & other)
{
  _messageType = Message::MessageType(other._messageType);
  _sender = other._sender;
  _seqNum = other._seqNum;
  
  return *this;
}

Message::MessageType Message::getMessageType()const
{
  return _messageType;
}

uint8_t Message::getSender()const
{
  return _sender;
}

unsigned short Message::getSequenceNumber()const
{
  return _seqNum;
}

void Message::setMessageType(const MessageType & messageType)
{
  _messageType = messageType;
}

void Message::setSender(const uint8_t & sender)
{
  _sender = sender;
}


void Message::setSequenceNumber(const unsigned short & seqNum)
{
  _seqNum = seqNum;
}

unsigned short Message::getSenderLevel()const
{
  return 0;
}

void Message::setSenderLevel(const unsigned short & senderLevel)
{
}

Alert Message::getAlert()const
{
  return Alert();
}

void Message::setAlert(const Alert & alert)
{
}

