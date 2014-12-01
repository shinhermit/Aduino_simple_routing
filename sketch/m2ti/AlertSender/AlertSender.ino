#include <XBee.h>
#include <SoftwareSerial.h>

#include <CommonValues.h>
#include <AlertMessage.h>
#include <MessageConverter.h>

XBee xbee = XBee();

unsigned short seqNum = 0;
float sensorValue = -10.0;

void setup() {
  
  xbee.begin(38400);
  
  Serial.begin(38400);
  Serial.println("Arduino. Will send packets.");
}

void loop() {
  
  delay(5000);
    
  // 64-bit addressing: This is the SH + SL address of remote XBee
  XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000FFFF);
  
  // Create an alert message
  sensorValue += 1.0;
  seqNum = (seqNum + 1) % CommonValues::Message::MAX_SEQUENCE_NUMBER;
  
  Alert alert(Message::ALERT, sensorValue);
  AlertMessage mess(0x40922070, seqNum, alert);
  
  // Serialize the message
  String serialMess = MessageConverter::serialize(mess);
  char strMess[serialMess.length()];
  serialMess.toCharArray(strMess, serialMess.length());

  Serial.println(String("Broadcasting message: ")+strMess);
  
  // Send xbee request
  XBeeAddress64 addr = XBeeAddress64(0x00000000, 0x0000FFFF);
  Tx64Request tx = Tx64Request(addr,//CommonValues::Message::BROADCAST_ADDRESS,
                                (uint8_t*)strMess,
                                sizeof(strMess));  
  // Send your request
  xbee.send(tx);

  TxStatusResponse txStatus = TxStatusResponse();
}
