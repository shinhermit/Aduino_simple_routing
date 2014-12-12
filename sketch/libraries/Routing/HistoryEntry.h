#ifndef HISTORY_ENTRY_H
#define HISTORY_ENTRY_H

#include <Arduino.h>
#include <stdint.h>
#include "String.h"

/**
* Entries for the message history.
*/
class HistoryEntry
{
  private:
    unsigned long _sender; /*!< The suffix of the address of the source. */
    
    unsigned short _seqNum; /*!< The sequence number of the message. */

    unsigned long _timeStamp; /*!< The time at which the message arrived (distinguish sequence number duplication from sequence number reset). */
    
  public:
    /// The previous entry in the linked list
    HistoryEntry * previous;
    /// The following entry in the linked list
    HistoryEntry * next;
    
    /// Constructor.
    /// \param sender the suffix of the address of the sender of the message associated with this history entry.
    /// \param seqNum the sequence number of the message associated with this history entry.
    /// \param timeStamp the time at which the message associated with this history entry arrived.
    HistoryEntry(const unsigned long & sender, const unsigned short & seqNum, const unsigned long & timeStamp);
    
    /// Constructor.
    HistoryEntry(const HistoryEntry & other);
    
    /// Update the entry to the lastest sequence number.<br/>
    /// <p>If the new information doest not represent a newer message, the update is ignored.</p>
    /// <p>A message is newer when it is not a dupplicated message.</p>
    /// <p>Duplicated messages are detected by the following rule:
    /// <code><pre>seqNum+ <= seqNum- AND timeStamp+ < maxDelay</pre></code>
    /// Where:
    /// <ul>
    /// <li>seqNum+ and timeStamp+ are the sequence number and timeStampe associated with the new message.</li>
    /// <li> seqNum- and timeStamp- are the sequence number and timeStampe associated with the currently known one.</li>
    /// <li>maxDelay is a parameter of the routing protocol which specifies the maximum time of retransmission of a message throrough the network.</li>
    /// </ul>
    /// \param seqNum the sequence number of the message associated with this history entry.
    /// \param timeStamp the time at which the message associated with this history entry arrived.
    void update(const unsigned short & seqNum, const unsigned long & timeStamp);
    
    /// operator ==
    /// Means that the other history entry represents the same message (thus a duplicate) than the message represented by this history entry.
    /// \return true if the other entry represents a duplicated message from the message associated with this entry.
    bool operator==(const HistoryEntry & other)const;
    
    /// operator >
    /// Means that the other history entry represents an older message (thus a duplicate) than the message represented by this history entry.
    /// \return true if the other entry represents an older message from the sender of the message associated with this history entry.
    bool operator >(const HistoryEntry & other)const;
    
    /// operator <
    /// Means that the other history entry represents a newer message (thus NOT a duplicate) than the message represented by this history entry.
    /// \return true if the other entry represents a newer message from the sender of the message associated with this history entry.
    bool operator <(const HistoryEntry & other)const;
    
    /// Provides the suffix of the address of the sender of the message associated with this history entry.
    /// \return the suffix of the address of the sender of the message.
    unsigned long sender()const;

    /// Provides the sequence number of the message associated with this history entry.
    /// \return the sequence number of the message associated with this history entry.
    unsigned short sequenceNumber()const;

    /// Provides the time at which the message associated with tis history entry arrived.
    /// \return the time at which the message associated with tis history entry arrived.
    unsigned long timeStamp()const;

    /// \return a pretty printed string representation of this history entry.
    String toString()const;
};

#endif
