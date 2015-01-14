#include <stdlib.h> /* strtof */

#include "MessageConverter.h"
#include "CommonValues.h"
#include "AlertMessage.h"
#include "DiscoveryMessage.h"
#include "Utility.h"

#include <SoftwareSerial.h>

String MessageConverter::serialize(const Message & mess)
{
  const String & prefix = CommonValues::Message::Serialization::PREFIX;
  const String & sep = CommonValues::Message::Serialization::SEPERATOR;
  
  char sender[9];
  String messageType = "";
  String senderLevel = "";
  String seqNum = "";
  String alertType = "";
  String sensorValue = "";
  
  // Always present
  sprintf(sender, "%08lX", mess.getSender());
  messageType += int(mess.getMessageType());
  seqNum += int(mess.getSequenceNumber());
  senderLevel += int(mess.getSenderLevel());
  
  // Alert only
  if(mess.getMessageType() == Message::ALERT)
  {
    alertType += int(mess.getAlert().getAlertType());
    Serial.println("");
    sensorValue += Utility::Convert::floatToString(mess.getAlert().getSensorValue());
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
  Serial.print("parsing: ");
  Serial.println(mess);
  const unsigned short NB_TOKENS = 6;
  const String & sep = CommonValues::Message::Serialization::SEPERATOR;
  
  Message * message;
  
  Message::MessageType messageType;
  unsigned long sender;
  unsigned short seqNum;
  
  unsigned short senderLevel;
  
  Alert alert(0);
  
  String tokens[NB_TOKENS];
  MessageConverter::getTokens(mess, sep, NB_TOKENS, tokens);
  
  char hexString[9];
  tokens[0].toCharArray(hexString, 9);
  sender = strtoul(hexString, (char**)0, 16);

  messageType = (Message::MessageType)tokens[1].toInt();
  senderLevel = (unsigned short)tokens[2].toInt();
  seqNum = (unsigned short)tokens[3].toInt();
   
  switch(messageType)
  {
  case Message::ALERT:
	//TODO : remove
	Serial.println("Alert parsed");
      alert.setAlertType((unsigned short)tokens[4].toInt());
      alert.setSensorValue(Utility::Convert::stringToFloat(tokens[5]));
      
      message = new AlertMessage(sender, seqNum, senderLevel, alert);
      break;
    case Message::DISCOVERY:
	//TODO : remove
	Serial.println("Discovery parsed");
      
      message = new DiscoveryMessage(sender, seqNum, senderLevel);
      break;
  }
 
	//TODO : remove
	Serial.println("Parsing done");
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

