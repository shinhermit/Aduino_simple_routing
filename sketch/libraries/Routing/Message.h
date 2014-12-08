#ifndef MESSAGE_H
#define MESSAGE_H

#include "Alert.h"

/**
 * Represents a message which can be sent to a node on the arduino
 * network.
 */
class Message
{
 public:

  /**
   * Represents the defferent types of message which ar exchanged between the nodes in the arduino network.
   */
  enum MessageType
  {
    ALERT = 0, /**< A Message which carries an alert. */
    DISCOVERY = 1 /**< A message which carries path discovery information.*/
  };
  
  /// The default type of messages.
  static const MessageType DEFAULT_TYPE;

  /**
   * Creates a Message which can be sent by the nodes on the network (after serialization).
   * \param type the type of message.
   * \param sender the suffix of the address of the sender (the last 8 hexa numbers of the MAC address).
   * \param seqNum the sequence number of the message.
   */
  Message(const MessageType & type, const unsigned long & sender,
		 const unsigned short & seqNum);

  /**
   * Creates a Message which can be sent by the nodes on the network (after serialization).
   * \param sender the suffix of the address of the sender (the last 8 hexa numbers of the MAC address).
   * \param seqNum the sequence number of the message.
   */
  Message(const unsigned long & sender, const unsigned short & seqNum);

  /**
   * Copy constructor.
   */  
  Message(const Message & other);
  
  /**
   * Creates a Message which can be sent by the nodes on the network (after serialization).
   */
  Message();
  
  /**
   * Operator =
   */
  Message & operator=(const Message & other);

  /**
   * Provides the type of information carried by this message.
   * \return  the type of information carried by this message.
   */
  MessageType getMessageType()const;

  /**
   * Provides the suffix of the address of the sender (the last 8 hexa numbers of the MAC address).
   * \return  the suffix of the address of the sender (the last 8 hexa numbers of the MAC address).
   */
  unsigned long getSender()const;

  /**
   * Provides the sequence number associated with this message.
   * \return the sequence number associated with this message.
   */
  unsigned short getSequenceNumber()const;

  void setMessageType(const MessageType & type);
  void setSender(const unsigned long & sender);
  void setSequenceNumber(const unsigned short & seqNum);
  
  // For subclasses
  /**
   * Should be overriden.
   * <p>In case of a path discovery message, provides the level of the node which was the last to forward this discovery message.</p>
   * \return  the level of the node which was the last to forward this discovery message.
   */
  virtual unsigned short getSenderLevel()const;

  /**
   * Should be overriden.
   * <p>In case of an alert message, provides the carried alert.</p>
   * \return  the carried alert.
   */
  virtual Alert getAlert()const;

  /**
   * Should be overriden.
   * <p>In case of a path discovery message, defines the level of the node which is the last to forward this discovery message.</p>
   * \param senderLevel  the level of the node which is the last to forward this discovery message.
   */
  virtual void setSenderLevel(const unsigned short & senderLevel);

  /**
   * Should be overriden.
   * <p>In case of an alert message, defines the carried alert.</p>
   * \param alert  the carried alert.
   */
  virtual void setAlert(const Alert & alert);
  
 private:
  /// the type of this message.
  MessageType _messageType;
  /// The suffix of the address of the sender (the last 8 hexa numbers of the MAC address).
  unsigned long _sender;
  /// the sequence number of this message.
  unsigned short _seqNum;

};

#endif

