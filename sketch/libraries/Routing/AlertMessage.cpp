#include "AlertMessage.h"

AlertMessage::AlertMessage(const unsigned long & sender, const unsigned short & seqNum,
		 const unsigned short & senderLevel, const Alert & alert)
  :Message::Message(Message::ALERT, sender, seqNum, senderLevel),
  _alert(alert)
{}

AlertMessage::AlertMessage(const AlertMessage & other)
  :Message::Message(other),
  _alert(other._alert)
{}
  
AlertMessage & AlertMessage::operator=(const AlertMessage & other)
{
  Message::operator=(other);
  
  _alert = other._alert;
  
  return *this;
}

Alert AlertMessage::getAlert()const
{
  return _alert;
}

void AlertMessage::setAlert(const Alert & alert)
{
  _alert = alert;
}


String AlertMessage::_getSpecialString()const
{
  return String("\t")+_alert.toString();
}
