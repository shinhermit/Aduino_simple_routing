#include "SourceNode.h"
#include "CommonValues.h"
#include "MessageConverter.h"
#include "AlertMessage.h"

#include <SoftwareSerial.h>

SourceNode SourceNode::_instance = SourceNode::SourceNode();

void SourceNode::initialize()
{
	_xbee.begin(CommonValues::Routing::XBEE_RATE);
}

SourceNode::SourceNode()
:_seqNum(0),
 	 _broadcast(true),
	_myAddress(0),
	_gatewayToSink(0),
	_lastDiscoverySequenceNumber(0),
	_lastAlertSequenceNumber(0),
	_xbee(),
	_rx16(),
	_rx64(),
	_history()
{
	initialize();
}

SourceNode::SourceNode(const SourceNode & other)
:_seqNum(other._seqNum),
 	 _broadcast(other._broadcast),
	_myAddress(other._myAddress),
	_gatewayToSink(other._gatewayToSink),
	_lastDiscoverySequenceNumber(other._lastDiscoverySequenceNumber),
	_lastAlertSequenceNumber(other._lastAlertSequenceNumber),
	_xbee(other._xbee),
	_rx16(other._rx16),
	_rx64(other._rx64),
	_history(other._history)
{
	initialize();
}

SourceNode & SourceNode::getInstance()
{
	return SourceNode::_instance;
}

void SourceNode::setAddress(const unsigned long & myAddress)
{
	_myAddress = myAddress;
}

String SourceNode::receiveMessage()
{
	char* data;
	uint8_t data_len;

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

void SourceNode::sendSensorValue () 
{
	unsigned short alertType = CommonValues::Alert::DEFAULT_ALERT_TYPE; 
	float sensorValue = 8.99;

	Alert alert(alertType, sensorValue);
	AlertMessage message(
		_myAddress,
		getSequenceNumber(),
		alert
	);

	broadcastMessage(message);
}

unsigned short SourceNode::getSequenceNumber()
{
	_lastAlertSequenceNumber = (_lastAlertSequenceNumber + 1) % 256;

	return _lastAlertSequenceNumber;
}

/// Attempts to read message, returns true if successful, false otherwise
bool SourceNode::processMessage() {
	String strMess;
	Message * mess;
	bool isNew;
	bool messageProcessed = false;
	unsigned long timeStamp;

	Serial.println("\nChecking for messages.");

	_xbee.readPacket();

	if (_xbee.getResponse().isAvailable())
	{
	  timeStamp = millis();

		messageProcessed = true;
		Serial.println("Message available.");

		strMess = receiveMessage();

		mess = MessageConverter::parse(strMess);

		if(mess->getMessageType() == Message::ALERT)
		{

		  isNew = _history.add(mess->getSender(), mess->getSequenceNumber(), timeStamp);
			if(isNew)
			{
				//new alert detected
				Serial.print("\n\n\nReceived alert from ");
				Serial.print(mess->getSender());
				Serial.println(".");
				Serial.print("\tType alerte: ");
				Serial.print(mess->getAlert().getAlertType());
				Serial.print(", valeur: ");
				Serial.println(mess->getAlert().getSensorValue());
				Serial.print("\n\n");

				if (_level > 0 && mess->getSenderLevel() > _level) 
				{
					//TODO Check test
					//our level is set since != 0
					//Message originates from sender with higher level	
					Alert alert(mess->getAlert().getAlertType(), mess->getAlert().getSensorValue());
					AlertMessage message(
						mess->getSender(),
						mess->getSequenceNumber(),
						alert
					);

					if (_broadcast)
					{
						broadcastMessage(message);
					}
					else
					{
						unicastMessageToSink(message);
					}
				}
			}
			else
			{
				Serial.println(String("Message ")+strMess+String(" found in history."));
			}
		}
		else
		{
			//Discovery message
			if (_level == 0 || _lastDiscoverySequenceNumber != mess->getSequenceNumber())
			{
				//set level, record sequence number, gateway to sink then broadcast
				//if first discovery or new sequence number
				_level = mess->getSenderLevel() + 1;
				_lastDiscoverySequenceNumber = mess->getSequenceNumber();
				_gatewayToSink = mess->getSender();
				DiscoveryMessage message(
					_myAddress,
					_lastDiscoverySequenceNumber,
					_level
				);

				if (_broadcast)
				{
					broadcastMessage(message);
				}
				else
				{
					unicastMessageToSink(message);
				}
			}


			/*Serial.print("\n\n\nReceived discovery from ");
			Serial.print(mess->getSender());
			Serial.println(".");
			Serial.println("Sender level : "+String(mess->getSenderLevel()));
			Serial.println("My level : "+String(_level));
			Serial.println("Sequence number : "+String(mess->getSequenceNumber()));
			Serial.print("\n\n");*/
		}

		delete mess;
	}

	return messageProcessed;
}

/// Process all available messages.
void SourceNode::processMessages()
{
	while(processMessage())
		;
}

void SourceNode::sendMessage(XBeeAddress64 & addr, const Message & mess)
{
	String serializedMess = MessageConverter::serialize(mess);
	char strMess[serializedMess.length()];
	serializedMess.toCharArray(strMess, serializedMess.length());

	Tx64Request tx = Tx64Request(addr, (uint8_t*)strMess, sizeof(strMess));
	_xbee.send(tx);

	TxStatusResponse txStatus = TxStatusResponse();
}

void SourceNode::unicastMessageToSink(const Message & mess)
{
	Serial.println("About to send unicast message to gateway");

	XBeeAddress64 addr = XBeeAddress64(
		CommonValues::Message::MAC_PREFIX,
		_gatewayToSink
	);

	sendMessage(addr, mess);

	Serial.println("\n\nDone sending message to gateway");
}

void SourceNode::broadcastMessage(const Message & mess)
{
	Serial.println("About to broadcast message");

	XBeeAddress64 addr = XBeeAddress64(
		CommonValues::Message::BROADCAST_PREFIX,
		CommonValues::Message::BROADCAST_SUFFIX
	);

	sendMessage(addr, mess);

	Serial.println("\n\nDone broadcasting message");
}
