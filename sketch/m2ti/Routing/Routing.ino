#include <Alert.h>
#include <AlertMessage.h>
#include <DiscoveryMessage.h>
#include <Message.h>
#include <MessageConverter.h>
#include <CommonValues.h>


#include <SoftwareSerial.h>

void printMessage(const Message & mess)
{
  Serial.println(String("sender: ")+mess.getSender()
                 +String(", messageType: ")+mess.getMessageType()
                 +String(", senderLevel: ")+mess.getSenderLevel()
                 +String(", sequence number: ")+mess.getSequenceNumber()
                 +String(", alert type: ")+mess.getAlert().getAlertType()
                 +String(", sensor value: ")+mess.getAlert().getSensorValue()
                 );
}

void setup()
{
  Serial.begin(CommonValues::Routing::XBEE_RATE);
  
  Alert alert(10, 2.1f);
  AlertMessage alertMessage(0x40762066, 3, alert);
  DiscoveryMessage discoveryMessage(0x40762066, 3, 20);
  
  Serial.println("Serializing");
  Serial.println( MessageConverter::serialize(alertMessage) );
  Serial.println( MessageConverter::serialize(discoveryMessage) );
  
  uint8_t sink = 0x40762066;
  unsigned short seqNum = 3;
  unsigned short senderLevel = 20;
  unsigned short alertType = 10;
  float sensorValue = 2.1;
  String strAlert = String("/@")+sink+String("#")+0+String("##")+seqNum+String("#")+alertType+String("#")+sensorValue;
  String strDiscovery = String("/@")+sink+String("#")+1+String("#")+senderLevel+String("#")+seqNum+String("##");
  
  Serial.println("Messages to parse:");
  Serial.println( strAlert );
  Serial.println( strDiscovery );
  
  Serial.println("Parsing.");
  Message * parsedAlert = MessageConverter::parse(strAlert);
  Message * parsedDiscovery = MessageConverter::parse(strDiscovery);

  // DEBUG
  printMessage(*parsedAlert);
  printMessage(*parsedDiscovery);
  
  Serial.println("Serializing parsed");
  Serial.println( MessageConverter::serialize(*parsedAlert) );
  Serial.println( MessageConverter::serialize(*parsedDiscovery) );
  
  delete parsedAlert;
  delete parsedDiscovery;
}

void loop()
{
}

