#include <XBee.h>
#include <SoftwareSerial.h>

#include <CommonValues.h>
#include <AlertMessage.h>
#include <MessageConverter.h>

#include <Lcd.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


XBee xbee = XBee();

unsigned short seqNum = 0;
float sensorValue = -10.0;

void setup()
{
  
  xbee.begin(CommonValues::Routing::XBEE_RATE);
  
  Serial.begin(CommonValues::Routing::XBEE_RATE);
  
  Serial.println("Arduino. Will send packets.");
}

void loop()
{
    
  // Create an alert message
  sensorValue += 1.0;
  seqNum = (seqNum + 1) % CommonValues::Message::SEQUENCE_NUMBER_MOD;
  
  Alert alert(Message::ALERT, sensorValue);
  AlertMessage mess(0x4086D82E, seqNum, alert);
  
  // Serialize the message
  String serialMess = MessageConverter::serialize(mess);
  char strMess[serialMess.length()];
  serialMess.toCharArray(strMess, serialMess.length());

  Serial.println(String("\nBroadcasting message: ")+strMess);
  
  // Send xbee request
  XBeeAddress64 addr64 = XBeeAddress64(
			    CommonValues::Message::BROADCAST_PREFIX,
			    CommonValues::Message::BROADCAST_SUFFIX);
  
  Tx64Request tx = Tx64Request(addr64,
                                (uint8_t*)strMess,
                                sizeof(strMess));
  // Send your request
  xbee.send(tx);

  TxStatusResponse txStatus = TxStatusResponse();
  
  delay(CommonValues::Routing::SOURCE_DELAY);
}
