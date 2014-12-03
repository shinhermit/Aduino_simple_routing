#include "SourceNode.h"
#include "MessageConverter.h"
#include "AlertMessage.h"
#include "CommonValues.h"

#include <SoftwareSerial.h>

SourceNode::SourceNode(const uint8_t & myAddress, AbstractSensor & sensor)
  :_myAddress(myAddress),
  _sensor(&sensor),
  _xbee(),
  _level(0),
  _lastDiscoverySequence(0),
  _lastAlertSequence(0),
  _firstDiscovery(true)   
{
  _xbee.begin(CommonValues::Routing::XBEE_RATE);
}

SourceNode::SourceNode()
  :_myAddress(0),
  _sensor(NULL),
  _xbee(),
  _level(0),
  _lastDiscoverySequence(0),
  _lastAlertSequence(0),
  _firstDiscovery(true)   
{
  _xbee.begin(CommonValues::Routing::XBEE_RATE);
}

void SourceNode::initialize(const uint8_t & myAddress, AbstractSensor & sensor)
{
  _myAddress = myAddress;
  _sensor = &sensor;
}

String SourceNode::receiveMessage()
{
  char* data;
  uint8_t data_len;
  
  _xbee.readPacket();
  
  if (_xbee.getResponse().getApiId() == RX_16_RESPONSE)
  {
    _xbee.getResponse().getRx16Response(_rx16);
    
    data = (char*)_rx16.getData();
    data_len = _rx16.getDataLength();     
  } 
  else if (_xbee.getResponse().getApiId() == RX_64_RESPONSE)
  {
    _xbee.getResponse().getRx64Response(_rx64);
    
    data = (char*)_rx64.getData();
    data_len = _rx64.getDataLength();
  }
  
  return String(data);
}

//Process broadcast messages
void SourceNode::processMessages()
{

  Serial.println("\nAbout to processMessages()");
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

        Serial.println("New message discovered");
        //new message received
        
        //if message type == ALERT => forward if discovery already received
        if (mess->getMessageType() == Message::ALERT) 
        {
            Serial.println("Alert");
            if (_level > 0)//discovery already received 
            {
                //forward alert on route to sink without modification
                _sendString(strMess);
                //sendAlert(mess->getAlert());
             }

        } 
        else 
        {
            Serial.println("Discovery");
            //discovery message
            if (_lastDiscoverySequence != mess->getSequenceNumber() && !_firstDiscovery)
            {
                Serial.println("Setting own level");
                _firstDiscovery = true;
                _level = mess->getSenderLevel() + 1;
                mess->setSenderLevel(_level);
                _sendString(MessageConverter::serialize(* mess));
            }
        }
    }
    
      
  }
    
  delete mess;
}

/*void SourceNode::processMessages()
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
    unsigned short senderLevel = mess->getSenderLevel();

    if (_history.add(mess->getSender(), mess->getSequenceNumber())) 
    
        //new message received
        if (senderLevel > _level && mess->getMessageType() == Message::ALERT) 
        {
            //forward alert on route to sink without modification
            _sendString(strMess);
        } 
        else 
        {
            //discovery message, let's set our level if apprpriate
            if (mess->getMessageType() == Message::DISCOVERY) 
            {
                if (_level == 0) 
                {
                    _level = senderLevel + 1;
                    //update senderLevel in message
                    mess->setSenderLevel(_level);
                }
            }
        }
    }
    
      
  }
    
  delete mess;
}
*/

float SourceNode::readSensor()const
{
  return _sensor->readValue();
}

void SourceNode::forwardAlert(const Alert & alert)
{
        
}

void SourceNode::sendAlert(const Alert & alert)
{
  AlertMessage alertMessage(_myAddress, _getAlertSequenceNumber(), alert);

  _sendString(MessageConverter::serialize(alertMessage));
}

void SourceNode::sendDiscovery(const DiscoveryMessage & discovery)
{
}

void SourceNode::sendMessage(const Message & message)
{
}


void SourceNode::_sendString(const String & message)
{
  // Serialize the message
  char strMess[message.length()];
  message.toCharArray(strMess, message.length());

  Serial.println(String("\nSending ")+strMess);
  
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
