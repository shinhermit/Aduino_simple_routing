#include "SinkNode.h"
#include "CommonValues.h"
#include "MessageConverter.h"

#include <SoftwareSerial.h>

SinkNode SinkNode::_instance = SinkNode::SinkNode();

void SinkNode::initialize()
{
  _xbee.begin(CommonValues::Routing::XBEE_RATE);
}

SinkNode::SinkNode()
  :_seqNum(0),
  _xbee(),
  _rx16(),
  _rx64(),
  _history()
{
  initialize();
}

SinkNode::SinkNode(const SinkNode & other)
  :_seqNum(other._seqNum),
  _xbee(other._xbee),
  _rx16(other._rx16),
  _rx64(other._rx64),
  _history(other._history)
{
  initialize();
}

SinkNode & SinkNode::getInstance()
{
  return SinkNode::_instance;
}

String SinkNode::receiveMessage()
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

bool SinkNode::isNew(const Message & mess)const
{
  HistoryEntry * old = _history.findEntry(mess.getSender());
  
  if(old == NULL)
  {
    return true;
  }
  else
  {
    return (*old) < HistoryEntry(mess.getSender(), mess.getSequenceNumber());
  }
}

void SinkNode::processMessages()
{
  String strMess;
  Message * mess;

  if (_xbee.getResponse().isAvailable())
  {
    strMess = receiveMessage();
    
    mess = MessageConverter::parse(strMess);
    
    if(mess->getMessageType() == Message::ALERT
        && isNew(*mess))
    {
      Serial.print("Received alert from ");
      Serial.print(mess->getSender());
      Serial.println(".");
      Serial.print("\tType alerte: ");
      Serial.print(mess->getAlert().getAlertType());
      Serial.print(", valeur: ");
      Serial.println(mess->getAlert().getSensorValue());
      
      _history.add(mess->getSender(), mess->getSequenceNumber());
    }
    
    delete mess;
  }
}

void SinkNode::broadcastMessage(const DiscoveryMessage & mess)
{
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
  _xbee.send(tx);

  TxStatusResponse txStatus = TxStatusResponse();
}

void SinkNode::discover()
{
  unsigned short maxSeq = CommonValues::Message::MAX_SEQUENCE_NUMBER;

  DiscoveryMessage mess(
        CommonValues::Message::SINK_SUFFIX,
        _seqNum,
        CommonValues::Routing::SINK_LEVEL);
        
  broadcastMessage(mess);
  
  _seqNum = (_seqNum + 1) % maxSeq;
}

