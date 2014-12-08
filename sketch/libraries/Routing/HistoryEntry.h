#ifndef HISTORY_ENTRY_H
#define HISTORY_ENTRY_H

#include <stdint.h>

/**
* Entries for the message history.
*/
class HistoryEntry
{
  private:
    uint8_t _sender; /*!< The suffix of the address of the source. */
    
    unsigned short _seqNum; /*!< The sequence number of the message. */
    
  public:
    /// The previous entry in the linked list
    HistoryEntry * previous;
    /// The following entry in the linked list
    HistoryEntry * next;
    
    /// Creates an history entry which represents a message (it's sequence number) sent by a certain node.
    /// \param sender the suffix of the address of the sender of the message (the 8 last hexa digits of the sender's address).
    /// \param seqNum the sequence number of the received message.
    HistoryEntry(const uint8_t & sender, const unsigned short & seqNum);
    
    /// Copy constructor.
    HistoryEntry(const HistoryEntry & other);
    
    /// Update the entry to the lastest sequence number.<br/>
    /// If the given sequence number is not newer than the current one, the update is ignored.
    /// \param seqNum the sequence number of the last received message.
    void update(const unsigned short & seqNum);
    
    /// operator == <br/>
    /// \return true if entries have same sender and same sequence number.
    bool operator==(const HistoryEntry & other)const;
    
    /// operator > <br/>
    /// \return true if entries have same sender and left entry has greater sequence number that right entry.
    bool operator >(const HistoryEntry & other)const;
    
    /// operator > <br/>
    /// \return true if entry has greater sequence number that the given sequence number.
    bool operator >(const unsigned short & seqNum)const;
    
    /// operator < <br/>
    /// \return true if entries have same sender and left entry has smaller sequence number that right entry.
    bool operator <(const HistoryEntry & other)const;
    
    /// Provides the suffix of the address of the sender associated with this entry.
    /// \return the suffix of the address of the sender associated with this entry.
    uint8_t sender()const;

    /// Provides the sequence number of the message associated with this entry.
    /// \return the sequence number of the message associated with this entry.
    unsigned short sequenceNumber()const;
};

#endif
