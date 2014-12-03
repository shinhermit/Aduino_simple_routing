#include <XBee.h>

#include <Alert.h>
#include <AlertMessage.h>
#include <DiscoveryMessage.h>
#include <Message.h>
#include <MessageConverter.h>
#include <CommonValues.h>
#include <String.h>


#include <SoftwareSerial.h>

void setup()
{
  Serial.begin(CommonValues::Routing::XBEE_RATE);
  
  Alert alert(10, 2.1f);
  AlertMessage alertMessage(0x40762066, 3, alert);
  DiscoveryMessage discoveryMessage(0x40762066, 3, 20);
  
  Serial.println("Serializing");
  Serial.println( MessageConverter::serialize(alertMessage) );
  Serial.println( MessageConverter::serialize(discoveryMessage) );
  
  String sink = "40762066";
  unsigned short seqNum = 3;
  unsigned short senderLevel = 20;
  unsigned short alertType = 10;
  String sensorValue = "2.1";
  String strAlert = String("/@")+sink+String("#")+0+String("##")+seqNum+String("#")+alertType+String("#")+sensorValue;
  String strDiscovery = String("/@")+sink+String("#")+1+String("#")+senderLevel+String("#")+seqNum+String("##");
  
  Serial.println("Parsing");
  Serial.println( strAlert );
  Serial.println( strDiscovery );
  
  Message * parsedAlert = MessageConverter::parse(strAlert);
  Message * parsedDiscovery = MessageConverter::parse(strDiscovery);
  
  Serial.println("Serializing parsed");
  Serial.println( MessageConverter::serialize(*parsedAlert) );
  Serial.println( MessageConverter::serialize(*parsedDiscovery) );
  
  delete parsedAlert;
  delete parsedDiscovery;
}

void loop()
{
}
