#include "MessageConverter.h"
#include "CommonValues.h"
#include "AlertMessage.h"
#include "DiscoveryMessage.h"
#include <math.h>

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
  String res;

  Serial.println("MessageConverter::Serializing");
  Serial.println(String("sender: ")+mess.getSender()
                 +String(", messageType: ")+mess.getMessageType()
                 +String(", senderLevel: ")+mess.getSenderLevel()
                 +String(", sequence number: ")+mess.getSequenceNumber()
                 +String(", alert type: ")+mess.getAlert().getAlertType()
                 +String(", sensor value: ")+mess.getAlert().getSensorValue()
                 );
  
  // Always present
  sender += int(macPrefix*pow(16, 4) + mess.getSender());
  messageType += int(mess.getMessageType());
  seqNum += int(mess.getSequenceNumber());
  Serial.println(String("Sequence number: ")+seqNum);
  
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
  
  res = prefix +
         sender + sep +
         messageType + sep +
         senderLevel + sep +
         seqNum + sep +
         alertType + sep +
         sensorValue;
  Serial.println(String("Result: ")+res);

  return res;
}

String MessageConverter::floatToString(const float & val)
{
  int ent, dec;

  ent = int(val);
  dec = int((val - ent)*100);

  return String("")+ent+String(".")+dec;
}

Message * MessageConverter::parse(const String & mess)
{
  Serial.println("MessageConverter::Parsing");

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

  // DEBUG
  for(int i = 0; i < NB_TOKENS; ++i)
    {
      Serial.println(String("token ")+i+String(": ")+String(tokens[i]));
    }
  
  sender = (uint8_t) tokens[0].toInt();
  messageType = (Message::MessageType)tokens[1].toInt();
  seqNum = (unsigned short)tokens[3].toInt();

  // DEBUG
  Serial.println(String("Fetched sender: ")+sender); 
  Serial.println(String("Fetched messageType: ")+messageType);
  Serial.println(String("Fetched seqNum: ")+seqNum);
   
  switch(messageType)
  {
  case Message::ALERT:
      alert.setAlertType((unsigned short)tokens[4].toInt());
      alert.setSensorValue(tokens[5].toFloat());
      
      //DEBUG
      Serial.println(String("Fetched alert type: ")+alert.getAlertType()); 
      Serial.println(String("Fetched sensor value: ")+alert.getSensorValue());
      
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

