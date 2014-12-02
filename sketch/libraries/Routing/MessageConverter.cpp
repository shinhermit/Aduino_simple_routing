#include "MessageConverter.h"
#include "CommonValues.h"
#include "AlertMessage.h"
#include "DiscoveryMessage.h"

#include <math.h>
#include <stdlib.h>

#include <SoftwareSerial.h>

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
  sender += String(mess.getSender(), HEX);
  messageType += int(mess.getMessageType());
  seqNum += int(mess.getSequenceNumber());
  
  // Discovery only
  if(mess.getMessageType() == Message::DISCOVERY)
  {
    senderLevel += int(mess.getSenderLevel());
  }
  
  // Alert only
  if(mess.getMessageType() == Message::ALERT)
  {
    alertType += int(mess.getAlert().getAlertType());
    sensorValue += floatToString(mess.getAlert().getSensorValue());
  }
  
  return prefix +
         sender + sep +
         messageType + sep +
         senderLevel + sep +
         seqNum + sep +
         alertType + sep +
         sensorValue;
}

String MessageConverter::floatToString(const float & val)
{
  int ent, dec;

  ent = int(val);
  dec = int((val - ent)*1000);

  return String("")+ent+String(".")+dec;
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
  
  char hexString[8];
  tokens[0].toCharArray(hexString, 8);
  sender = strtoul(hexString, (char**)0, 0);

  messageType = (Message::MessageType)tokens[1].toInt();
  seqNum = (unsigned short)tokens[3].toInt();
   
  switch(messageType)
  {
  case Message::ALERT:
      alert.setAlertType((unsigned short)tokens[4].toInt());
      alert.setSensorValue(tokens[5].toFloat());
      
      message = new AlertMessage(sender, seqNum, alert);
      break;
    case Message::DISCOVERY:
      senderLevel = (unsigned short)tokens[2].toInt();
      
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

