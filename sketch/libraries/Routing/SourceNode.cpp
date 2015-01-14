#include <SourceNode.h>
#include <CommonValues.h>
#include <MessageConverter.h>
#include <Utility.h>
#include <AlertMessage.h>
#include <Lcd.h>
#include <math.h> // for abs()

#include <SoftwareSerial.h>

SourceNode SourceNode::_instance = SourceNode();

void SourceNode::initialize()
{
	_xbee.begin(CommonValues::Routing::XBEE_RATE);
}

SourceNode::SourceNode()
:_seqNum(0),
	_lastDiscoverySequence(0),
	_lastAlertTimestamp(0),
	_level(0),
 	 _broadcast(false),
	_myAddress(0),
	_firstGatewayToSink(0),
	_lastGatewayToSink(0),
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
	_lastDiscoverySequence(other._lastDiscoverySequence),
	_lastAlertTimestamp(other._lastAlertTimestamp),
	_level(other._level),
 	 _broadcast(other._broadcast),
	_myAddress(other._myAddress),
	_firstGatewayToSink(other._firstGatewayToSink),
	_lastGatewayToSink(other._lastGatewayToSink),
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

	unsigned long timeStamp = millis();
	unsigned long delay = abs(timeStamp - _lastAlertTimestamp);

	if (delay >= CommonValues::Routing::SOURCE_DELAY) 
	{
		//store time of alert
		_lastAlertTimestamp = timeStamp;

		//prepare and send alert
		Alert alert(alertType, sensorValue);
		AlertMessage message(
			_myAddress,
			getSequenceNumber(),
			_level,
			alert
		);

		send(message);


        //new alert received
		String value = Utility::Convert::floatToString(sensorValue);
        Lcd::getInstance()->display("[A]: START");
        Lcd::getInstance()->display("[A:value]: "+value);

        Serial.println("Sending alert : "+ String(value));
	}
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

	Serial.println(".");

	_xbee.readPacket();

	if (_xbee.getResponse().isAvailable())
	{
		Serial.println("\n<<<<<");
		messageProcessed = true;

		strMess = receiveMessage();
        if (!strMess.equals(""))
		{
            mess = MessageConverter::parse(strMess);
            isNew = _history.add(mess->getSender(), mess->getSequenceNumber());

            char humanReadableSender[9];
            sprintf(humanReadableSender, "%08lX", mess->getSender());
            Serial.println("Message available from "+String(humanReadableSender));

            if(isNew)
            {
                if(mess->getMessageType() == Message::ALERT)
                {	
                    //new alert received
                    Lcd::getInstance()->display("[A:sender]: "+String(humanReadableSender));
                    Serial.println("New alert received from "+String(humanReadableSender));

                    if (_level > 0 && mess->getSenderLevel() > _level) 
                    {
                        //TODO Check test : should relay all messages (whatever the level) ?
                        //our level is set since _level != 0
                        //Message originates from sender with higher level	
//                        Alert alert(mess->getAlert().getAlertType(), mess->getAlert().getSensorValue());
//                        AlertMessage message(
//                                mess->getSender(),
//                                mess->getSequenceNumber(),
//				mess->getSenderLevel(),
//                                alert
//                                );

                        send(*mess);

                        String sensorValue = Utility::Convert::floatToString(mess->getAlert().getSensorValue());
                        Lcd::getInstance()->display("[A:value]: " + sensorValue);
                        Serial.println("Value: " + sensorValue);
                    }
                    else 
                    {
                        //TODO
                        //_level not set yet, no discovery received
                        //store message for the moment
                        //Just drop it!
                        Lcd::getInstance()->display("[A:ignored]");
                        Serial.println("Alert ignored : no route to host yet or alert from lower level.");
                    }
                }
                else
                {
                    //Discovery message
                    //Is it a new discovery sequence ?
                    bool isNewDiscoverySequence = 
		      MessageHistory::isNewer(_lastDiscoverySequence, mess->getSequenceNumber());
                    //Were we part of a discovery newer than the incoming discovery
                    bool isOldDiscoverySequence = 
		      MessageHistory::isNewer(mess->getSequenceNumber(), _lastDiscoverySequence);

                    if (isNewDiscoverySequence || _level == 0)
                    {
                        //set level
                        _level = mess->getSenderLevel() + 1;
                        //record sequence nummber
                        _lastDiscoverySequence = mess->getSequenceNumber();
                        //store gateway to sink
                        _firstGatewayToSink = mess->getSender();

                        //Lcd and serial display
                        Lcd::getInstance()->display("[D]: START");
                        Lcd::getInstance()->newLine();
                        Serial.println("New discovery sequence");
                        Lcd::getInstance()->display("[D:level]: "+String(_level));
                        Serial.println("Discovery received from level " + String(mess->getSenderLevel()));
                        Serial.println("Setting level to "+String(_level));
                        //Prepare message and send message
                        DiscoveryMessage message(
                                _myAddress,
                                mess->getSequenceNumber(),
                                _level
                                );
                        send(message);

                    } 
                    else if (mess->getSequenceNumber() == _lastDiscoverySequence
                            &&
                            (mess->getSenderLevel() + 1) == _level)
                    {
                        //Store as gateway only if level == own level - 1
                        //New route to gateway discovered
                        _lastGatewayToSink = mess->getSender();	

                        Lcd::getInstance()->display("[D:+gw]: " + String(humanReadableSender));
                        Serial.println("New level "+String(mess->getSenderLevel())+" gateway");
                    }

                }
            }
            else
            {
                Serial.println(String("Duplicate message : ")+strMess+String(" found in history."));
            }

            delete mess;

        }
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
//	Serial.println("\n[[[[[");
//	Serial.println("Entering send(message)");
//	Serial.println("About to send\n"+mess.toString()+"\n");
//
//	if (mess.getMessageType() == Message::ALERT) 
//	{
//		Serial.println("Alert");
//		Serial.print("Type alerte: ");
//		Serial.println(mess.getAlert().getAlertType());
//		Serial.print("Valeur alert: ");
//		Serial.println(mess.getAlert().getSensorValue());
//	}
//	else 
//	{
//		Serial.println("Discovery");
//	}
//	Serial.println("Message sender level : "+String(mess.getSenderLevel()));
//	Serial.println("My level : "+String(_level));
//	Serial.println("Sequence number : "+String(mess.getSequenceNumber()));
//
	// no unicast on discovery messages
	if (_broadcast == false && mess.getMessageType() == Message::ALERT)
	{
		unicastMessageToSink(mess);
	}
	else
	{
		broadcastMessage(mess);
	}

//	Serial.println("Exiting send(message)");
//
//	Serial.println("]]]]]");
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
	sprintf(humanReadableSender, "%08lX", _firstGatewayToSink);

	if (_level > 0) 
	{
		Serial.println("About to send unicast message to" + String(humanReadableSender));

		XBeeAddress64 addr = XBeeAddress64(
			CommonValues::Message::MAC_PREFIX,
			_firstGatewayToSink
		);

		sendMessage(addr, mess);

		Serial.println("Done sending message to gateway");
	}
	else 
	{
		Serial.println("Could not send unicast message. Level not set yet");
	}
}

void SourceNode::broadcastMessage(const Message & mess)
{
	Serial.println("About to broadcast message");

	XBeeAddress64 addr = XBeeAddress64(
		CommonValues::Message::BROADCAST_PREFIX,
		CommonValues::Message::BROADCAST_SUFFIX
	);

	sendMessage(addr, mess);

	Serial.println("\nDone broadcasting message");
}
