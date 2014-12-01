#ifndef ALERT_MESSAGE_H
#define ALERT_MESSAGE_H

#include "Message.h"
#include "Alert.h"

class AlertMessage : public Message
{
 private:
  Alert _alert;

 public:

  AlertMessage(const uint8_t & sender, const unsigned short & seqNum,
		 const Alert & alert);

  AlertMessage(const AlertMessage & other);
  
  AlertMessage & operator=(const AlertMessage & other);

  virtual Alert getAlert()const;

  virtual void setAlert(const Alert & alert);
};

#endif

