#include "MessageConverter.h"
#include "CommonValues.h"
#include "AlertMessage.h"
#include "DiscoveryMessage.h"
#include <math.h>

String MessageConverter::serialize(const Message & mess)
{
  const uint8_t & macPrefix = CommonValues::Message::MAC_PREFIX;
  const String & prefix = CommonValues::Message::Serialization::PREFIX;
  const String & sep = CommonValues::Message::Serialization::SEPERATOR;
  
  String sender = "";
  String messageType = "";
  String senderLevel = "";
  String seqNum = "";
  String alertType = "";
  String sensorValue = "";
  
  // Always present
  sender += macPrefix*pow(16, 4) + mess.getSender();
  messageType += mess.getMessageType();
  seqNum += mess.getSequenceNumber();
  
  // Discovery only
  if(mess.getMessageType() == Message::DISCOVERY)
  {
    senderLevel += mess.getSenderLevel();
  }
  
  // Alert only
  if(mess.getMessageType() == Message::ALERT)
  {
    alertType += mess.getAlert().getAlertType();
    sensorValue += mess.getAlert().getSensorValue();
  }
  
  return prefix +
         sender + sep +
         messageType + sep +
         senderLevel + sep +
         seqNum + sep +
         alertType + sep +
         sensorValue;
}

Message * MessageConverter::parse(const String & mess)
{
  const unsigned short NB_TOKENS = 6;
  const String & sep = CommonValues::Message::Serialization::SEPERATOR;
  
  Message * message;
  
  Message::MessageType messageType;
  uint8_t sender;
  unsigned short seqNum;
  
  unsigned short senderLevel;
  
  Alert alert(0);
  
  String tokens[NB_TOKENS];
  MessageConverter::getTokens(mess, sep, NB_TOKENS, tokens);
  
  sender = (uint8_t) tokens[0].toInt();
  messageType = (Message::MessageType)tokens[1].toInt();
  seqNum = (unsigned short)tokens[2].toInt();
    
  switch(messageType)
  {
    case Message::ALERT:
      alert.setAlertType((unsigned short)tokens[4].toInt());
      alert.setSensorValue(tokens[5].toFloat());
      
      message = new AlertMessage(sender, seqNum, alert);
      break;
    case Message::DISCOVERY:
      senderLevel = (unsigned short)tokens[3].toInt();
      
      message = new DiscoveryMessage(sender, seqNum, senderLevel);
      break;
  }
  
  return message;
}

void MessageConverter::getTokens(const String & mess, const String & seperator,
                                 const unsigned short nbTokens, String * fillMe)
{
  unsigned short tokenStart, tokenEnd, i;
  
  tokenStart = 2; // ignore '/@'
  tokenEnd = mess.indexOf(seperator);
  i = 0;
  while(tokenEnd >= 0 && i < nbTokens)
  {
    if(mess.charAt(tokenStart) == seperator.charAt(0)) // empty token
    {
      fillMe[i] = "";
    }
    else
    {
      fillMe[i] = mess.substring(tokenStart, tokenEnd);
    }
    
    tokenStart = tokenEnd + 1;
    tokenEnd = mess.indexOf(seperator, tokenStart);
    ++i;
  }
}

