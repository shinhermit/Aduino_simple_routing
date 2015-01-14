#ifndef ALERT_MESSAGE_H
#define ALERT_MESSAGE_H

#include "Message.h"
#include "Alert.h"

/**
 * Specializes a Message, in order to which represents a message which
 * carries an alert.
 */
class AlertMessage : public Message
{
 private:
  /**
   * The alert carries by this message.
   */
  Alert _alert;

 protected:
  /**
   * \overload
   */
  virtual String _getSpecialString()const;

 public:
  /**
   * Creates a Message which carries the provided Alert.
   * \param sender the suffix of the address of the sender (last 8 hexa numbers of the MAC address.
   * \param seqNum the sequence number of the message.
   * \param senderLevel
   * \param alert the alert carried by this message.
   */
  AlertMessage(const unsigned long & sender, const unsigned short & seqNum,
	       const unsigned short & senderLevel, const Alert & alert);

  /**
   * Copy constructor.
   */
  AlertMessage(const AlertMessage & other);
  
  /**
   * Operator =
   */
  AlertMessage & operator=(const AlertMessage & other);

  /**
   * Provides the Alert carried by this message.
   * \return the Alert carried by this message.
   */
  virtual Alert getAlert()const;

  /**
   * Defines the Alert that this message must carry.
   * \param alert the Alert that this message must carry.
   */
  virtual void setAlert(const Alert & alert);
};

#endif

