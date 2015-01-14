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

    bool _duplicates(const HistoryEntry & other)const;
    bool _olderThan(const HistoryEntry & other)const;
    bool _newerThan(const HistoryEntry & other)const;
    
  public:
    /// The previous entry in the linked list
    HistoryEntry * previous;
    /// The following entry in the linked list
    HistoryEntry * next;
    
    /// Constructor.
    /// \param sender the suffix of the address of the sender of the message associated with this history entry.
    /// \param seqNum the sequence number of the message associated with this history entry.
    HistoryEntry(const unsigned long & sender, const unsigned short & seqNum);
    
    /// Copy constructor.
    HistoryEntry(const HistoryEntry & other);
    
    /// Updates the entry to the lastest sequence number.<br/>
    /// One should verify that the new information represents a newer message than the one represented by the current entry.
    void update(const unsigned short & seqNum);
    
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
