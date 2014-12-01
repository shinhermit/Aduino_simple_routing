#include <Alert.h>
#include <AlertMessage.h>
#include <DiscoveryMessage.h>
#include <Message.h>
#include <MessageConverter.h>
#include <CommonValues.h>


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
  
  uint8_t sink = 0x40762066;
  unsigned short seqNum = 3;
  unsigned short senderLevel = 20;
  unsigned short alertType = 10;
  float sensorValue = 2.1;
  String strDiscovery = String("/@")+sink+String("#")+1+String("#")+seqNum+String("#")+senderLevel+String("###");
  String strAlert = String("/@")+sink+String("#")+0+String("#")+seqNum+String("##")+alertType+String("#")+sensorValue;
  
  Serial.println("Parsing");
  Serial.println( strDiscovery );
  Serial.println( strAlert );
  
  Message * parsedDiscovery = MessageConverter::parse(strDiscovery);
  Message * parsedAlert = MessageConverter::parse(strAlert);
  
  Serial.println("Serializing parsed");
  Serial.println( MessageConverter::serialize(*parsedDiscovery) );
  Serial.println( MessageConverter::serialize(*parsedAlert) );
  
  delete parsedDiscovery;
  delete parsedAlert;
}

void loop()
{
}
