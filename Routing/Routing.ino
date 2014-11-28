#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();

uint8_t* payload;
uint8_t payload_len;

Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();

void setup() {

  xbee.begin(38400);
  Serial.begin(38400);

  Serial.println("Arduino. Will receive packets.");
}

void loop() {

  // read incoming pkt
  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    
    Serial.println("receive");
    
    // is it a response to the previously sent packet?            	
    if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
    
    }    
    
    if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
    
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
        xbee.getResponse().getRx16Response(rx16);
        
        payload = rx16.getData();
        payload_len=rx64.getDataLength();     
      } 
      else 
      {
        xbee.getResponse().getRx64Response(rx64);
        
        payload = rx64.getData();
        payload_len=rx64.getDataLength();
      }
          
      for (int i=0; i<payload_len; i++)
        Serial.print((char)payload[i]);
            
      Serial.println("\ndone");  
    } 
  } 
}


