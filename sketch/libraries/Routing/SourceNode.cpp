#include "SourceNode.h"
#include "MessageConverter.h"
#include "AlertMessage.h"
#include <../XBee/XBee.h>
#include "CommonValues.h"

SourceNode::SourceNode(const uint8_t & myAddress, AbstractSensor & sensor)
  :_myAddress(myAddress),
  _sensor(&sensor),
  _xbee()
{
  _xbee.begin(CommonValues::Routing::XBEE_RATE);
}

SourceNode::SourceNode()
  :_myAddress(0),
  _sensor(NULL),
  _xbee()
{
  _xbee.begin(CommonValues::Routing::XBEE_RATE);
}

void SourceNode::initialize(const uint8_t & myAddress, AbstractSensor & sensor)
{
  _myAddress = myAddress;
  _sensor = &sensor;
}

void SourceNode::processMessages()const
{
  //Can receive two types of messages
  // - alert to re broadcast
  // - discover messages
  String strMess;
  Message * mess;

  if (_xbee.getResponse().isAvailable())
  {
    strMess = receiveMessage();
    
    mess = MessageConverter::parse(strMess);
    
    if (_history.add(mess->getSender(), mess->getSequenceNumber())) 
    {
        //new message received
        if (mess->getMessageType() == Message::ALERT) {
            //forward alert on route to sink
            Alert alert = mess->getAlert();

        } else {
            //discover message, we will set our level

        }
    }
    
//      Serial.print("Received alert from ");
//      Serial.print(mess->getSender());
//      Serial.println(".");
//      Serial.print("\tType alerte: ");
//      Serial.print(mess->getAlert().getAlertType());
//      Serial.print(", valeur: ");
//      Serial.println(mess->getAlert().getSensorValue());
      
    }
    
    delete mess;
  }

}

float SourceNode::readSensor()const
{
  return _sensor->readValue();
}

void SourceNode::sendAlert(const Alert & alert)
{
  AlertMessage alertMessage(_myAddress, _getAlertSequenceNumber(), alert);

  _sendString(MessageConverter::serialize(alertMessage));
}

void SourceNode::_sendString(const String message)
{
  // Serialize the message
  char strMess[message.length()];
  message.toCharArray(strMess, message.length());
  
  // Send xbee request
  XBeeAddress64 addr = XBeeAddress64(0x00000000, 0x0000FFFF);
  Tx64Request tx = Tx64Request(addr,//CommonValues::Message::BROADCAST_ADDRESS,
                                (uint8_t*)strMess,
                                sizeof(strMess));
  _xbee.send(tx);

  TxStatusResponse txStatus = TxStatusResponse();
}

unsigned short SourceNode::_getAlertSequenceNumber() 
{
  if (_alertSequenceNumber > 255) {
    _alertSequenceNumber = 0;
  }

  return _alertSequenceNumber++;
} 
