#ifndef HISTORY_ENTRY_H
#define HISTORY_ENTRY_H

#include <Arduino.h>

/**
* Entries for the message history.
*/
class HistoryEntry
{
  private:
    unsigned long _sender; /*!< The suffix of the address of the source. */
    
    unsigned short _seqNum; /*!< The sequence number of the message. */

    unsigned long _timeStamp; /*!< The time at which the message arrived (distinguish sequence number duplication from sequence number reset). */

    bool _duplicates(const HistoryEntry & other)const;
    bool _olderThan(const HistoryEntry & other)const;
    bool _newerThan(const HistoryEntry & other)const;

    /// Calculates the absolute difference of two unsigned
    /// values.
    /// \param x one of the value implied in the difference
    /// \param y the other value implied in the difference.
    /// \return the absolute difference of the provided unsigned long values.
    long double _usingedDiff(const unsigned long & x, const unsigned long & y)const;
    
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
    
    /// Copy constructor.
    HistoryEntry(const HistoryEntry & other);
    
    /// Updates the entry to the lastest sequence number.<br/>
    /// One should verify that the new information represents a newer message than the one represented by the current entry.
    void update(const unsigned short & seqNum, const unsigned long & timeStamp);
    
    /// operator ==
    /// Means that the other history entry represents the same message (thus a duplicate) than the message represented by this history entry.
    /// \return true if the other entry represents a duplicated message from the message associated with this entry.
    bool isDuplicateOf(const HistoryEntry & other)const;
    
    /// operator >
    /// Means that the other history entry represents an older message (thus a duplicate) than the message represented by this history entry.
    /// \return true if the other entry represents an older message from the sender of the message associated with this history entry.
    bool isNewerThan(const HistoryEntry & other)const;
    
    /// operator <
    /// Means that the other history entry represents a newer message (thus NOT a duplicate) than the message represented by this history entry.
    /// \return true if the other entry represents a newer message from the sender of the message associated with this history entry.
    bool isOlderThan(const HistoryEntry & other)const;
    
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
