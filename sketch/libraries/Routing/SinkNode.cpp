#include <stdlib.h> /* strtof */

#include "SinkNode.h"
#include "CommonValues.h"
#include "MessageConverter.h"
#include "Utility.h"

#include <SoftwareSerial.h>

SinkNode SinkNode::_instance = SinkNode();

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
  unsigned long data_len;
  
  if (_xbee.getResponse().getApiId() == TX_STATUS_RESPONSE)
  {
  }
  else if (_xbee.getResponse().getApiId() == RX_16_RESPONSE)
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

bool SinkNode::processNextMessage()
{
  String strMess;
  Message * mess;
  bool isNew, wasAvailable = false;
  unsigned long timeStamp;

  //Serial.println("\nChecking message buffer.");

  _xbee.readPacket();

  if (_xbee.getResponse().isAvailable())
  {
    wasAvailable = true;

    //Serial.println("Message available.");

    strMess = receiveMessage();

    mess = MessageConverter::parse(strMess);
    
    if(mess->getMessageType() == Message::ALERT)
    {
	isNew = _history.add(mess->getSender(),
			     mess->getSequenceNumber());
      if(isNew)
      {
	Serial.println(mess->toString());
      }
      else
      {
	Serial.println(String("Message ")+strMess+String(" found in history."));
      }
    }
    else
    {
      Serial.println("Message is not an alert.");
    }
    
    delete mess;
  }

  return wasAvailable;
}

void SinkNode::processMessages()
{
  bool wasAvailable = false;
  do
  {
    wasAvailable = processNextMessage();
  }
  while(wasAvailable);
}

void SinkNode::broadcastMessage(const DiscoveryMessage & mess)
{
  // Serialize the message
  String serialMess = MessageConverter::serialize(mess);

  // + 1 on message length or /@sender#0#level#seqNum##
  // truncated to /@sender#0#level#seqNum#
  char strMess[serialMess.length() + 1];
  serialMess.toCharArray(strMess, serialMess.length() + 1);

  Serial.println(String("\nBroadcasting message: ")+strMess+" ; ");
  
  // Send xbee request
  XBeeAddress64 addr = XBeeAddress64(
			    CommonValues::Message::BROADCAST_PREFIX,
			    CommonValues::Message::BROADCAST_SUFFIX);
  Tx64Request tx = Tx64Request(addr, (uint8_t*)strMess, sizeof(strMess));
  _xbee.send(tx);

  TxStatusResponse txStatus = TxStatusResponse();
}

void SinkNode::discover()
{
  if(_myAddress == 0)
  {
    String macLow = Utility::Board::getMACLowPart(_xbee);
    Serial.println(macLow);
    char hexString[9];
    macLow.toCharArray(hexString, 9);
    _myAddress = strtoul(hexString, (char**)0, 16);
  }

  unsigned short seqMod = CommonValues::Message::SEQUENCE_NUMBER_MOD;

  DiscoveryMessage mess(
        _myAddress,
        _seqNum,
        CommonValues::Routing::SINK_LEVEL);
        
  broadcastMessage(mess);
  
  _seqNum = (_seqNum + 1) % seqMod;
}

