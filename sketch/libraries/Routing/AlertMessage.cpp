#include "AlertMessage.h"

AlertMessage::AlertMessage(const uint8_t & sender, const unsigned short & seqNum,
		 const Alert & alert)
  :Message::Message(Message::ALERT, sender, seqNum),
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

