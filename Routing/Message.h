#ifndef MESSAGE_H
#define MESSAGE_H

#include "Alert.h"
#include <stdint.h>

class Message
{
 public:

  enum MessageType
  {
    ALERT = 0,
    DISCOVERY = 1
  };
  
  static const MessageType DEFAULT_TYPE;

  Message(const MessageType & type, const uint8_t & sender,
		 const unsigned short & seqNum);

  Message(const uint8_t & sender, const unsigned short & seqNum);
  
  Message(const Message & other);
  
  Message();
  
  Message & operator=(const Message & other);

  MessageType getMessageType()const;
  uint8_t getSender()const;
  unsigned short getSequenceNumber()const;

  void setMessageType(const MessageType & type);
  void setSender(const uint8_t & sender);
  void setSequenceNumber(const unsigned short & seqNum);
  
  // For subclasses
  virtual unsigned short getSenderLevel()const;
  virtual Alert getAlert()const;

  virtual void setAlert(const Alert & type);
  virtual void setSenderLevel(const unsigned short & senderLevel);
  
 private:
  MessageType _messageType;
  uint8_t _sender;
  unsigned short _seqNum;

};

#endif

