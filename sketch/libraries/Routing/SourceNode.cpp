#include <SourceNode.h>
#include <CommonValues.h>
#include <MessageConverter.h>
#include <AlertMessage.h>
#include <Lcd.h>


#include <SoftwareSerial.h>

SourceNode SourceNode::_instance = SourceNode::SourceNode();

void SourceNode::initialize()
{
	_xbee.begin(CommonValues::Routing::XBEE_RATE);
}

SourceNode::SourceNode()
:_seqNum(0),
	_level(0),
 	 _broadcast(false),
	_myAddress(0),
	_gatewayToSink(0),
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
	_level(other._level),
 	 _broadcast(other._broadcast),
	_myAddress(other._myAddress),
	_gatewayToSink(other._gatewayToSink),
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

	send(message);
}

unsigned short SourceNode::getSequenceNumber()
{
	_lastAlertSequenceNumber = (_lastAlertSequenceNumber + 1) % 256;

	return _lastAlertSequenceNumber;
}

/// Attempts to read message, returns true if successful, false otherwise
bool SourceNode::processMessage() 
{
	String strMess;
	Message * mess;
	bool isNew;
	bool messageProcessed = false;
	unsigned long timeStamp;

	Serial.println("\nChecking for messages.");

		//LcdDisplay::getInstance().display("test");
	_xbee.readPacket();

	if (_xbee.getResponse().isAvailable())
	{
		Serial.println("\n<<<<<");
		timeStamp = millis();
		messageProcessed = true;

		strMess = receiveMessage();

		mess = MessageConverter::parse(strMess);
		isNew = _history.add(mess->getSender(), mess->getSequenceNumber(), timeStamp);

	    char humanReadableSender[9];
		sprintf(humanReadableSender, "%08lX", mess->getSender());
		Serial.println("Message available from "+String(humanReadableSender));

		if(isNew)
		{
			Serial.println("new");
			if(mess->getMessageType() == Message::ALERT)
			{	
				//new alert detected
				Lcd::getInstance().display("Alert");

				if (_level > 0/* && mess->getSenderLevel() > _level*/) 
				{
					//TODO Check test : should relay all messages (whatever the level) ?
					//our level is set since _level != 0
					//Message originates from sender with higher level	
					Alert alert(mess->getAlert().getAlertType(), mess->getAlert().getSensorValue());
					AlertMessage message(
						mess->getSender(),
						mess->getSequenceNumber(),
						alert
					);

					send(message);
				}
				else 
				{
					//TODO
					//_level not set yet, no discovery received
					//store message for the moment
					//Just drop it!
				}
			}
			else
			{
				//Discovery message
				//set level, record sequence number, gateway to sink then broadcast
				//if first discovery or new sequence number
				_level = mess->getSenderLevel() + 1;
				_gatewayToSink = mess->getSender();
				DiscoveryMessage message(
					_myAddress,
					mess->getSequenceNumber(),
					_level
				);

				send(message);

				Lcd::getInstance().display("Discovery");
				delay(250);
				Lcd::getInstance().display("My level : "+String(_level));
			}
		}
		else
		{
			Serial.println(String("Message ")+strMess+String(" found in history."));
		}

		delete mess;
		Serial.println(">>>>>");
	}

	return messageProcessed;
}

/// Process all available messages.
void SourceNode::processMessages()
{
	bool messageProcessed;

	do 
	{
		messageProcessed = processMessage();
	}
	while(messageProcessed);
}

void SourceNode::send(const Message & mess)
{
	Serial.println("\n[[[[[");
	Serial.println("Entering send(message)");
	Serial.println("About to send\n"+mess.toString()+"\n");

	if (mess.getMessageType() == Message::ALERT) 
	{
		Serial.println("Alert");
		Serial.print("Type alerte: ");
		Serial.println(mess.getAlert().getAlertType());
		Serial.print("Valeur alert: ");
		Serial.println(mess.getAlert().getSensorValue());
	}
	else 
	{
		Serial.println("Discovery");
	}
	Serial.println("Message sender level : "+String(mess.getSenderLevel()));
	Serial.println("My level : "+String(_level));
	Serial.println("Sequence number : "+String(mess.getSequenceNumber()));

	// no unicast on discovery messages
	if (_broadcast == false && mess.getMessageType() == Message::ALERT)
	{
		unicastMessageToSink(mess);
	}
	else
	{
		broadcastMessage(mess);
	}

	Serial.println("Exiting send(message)");

	Serial.println("]]]]]");
}

void SourceNode::sendMessage(XBeeAddress64 & addr, const Message & mess)
{
	String serializedMess = MessageConverter::serialize(mess);
	char strMess[serializedMess.length() + 1];
	serializedMess.toCharArray(strMess, serializedMess.length() + 1);

	Tx64Request tx = Tx64Request(addr, (uint8_t*)strMess, sizeof(strMess));
	_xbee.send(tx);

	TxStatusResponse txStatus = TxStatusResponse();
}

void SourceNode::unicastMessageToSink(const Message & mess)
{

	char humanReadableSender[9];
	sprintf(humanReadableSender, "%08lX", _gatewayToSink);

	Serial.println("About to send unicast message to" + String(humanReadableSender));

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
