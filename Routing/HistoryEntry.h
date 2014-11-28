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
    
    /// Constructor.
    HistoryEntry(const uint8_t & sender, const unsigned short & seqNum);
    
    /// Constructor.
    HistoryEntry(const HistoryEntry & other);
    
    /// Update the entry to the lastest sequence number.<br/>
    /// If the given sequence number is not newer than the current one, the update is ignored.
    void update(const unsigned short & seqNum);
    
    /// operator == <br/>
    /// true if entries have same sender and same sequence number.
    bool operator==(const HistoryEntry & other)const;
    
    /// operator > <br/>
    /// true if entries have same sender and left entry has greater sequence number that right entry.
    bool operator >(const HistoryEntry & other)const;
    
    /// operator > <br/>
    /// true if entry has greater sequence number that the given sequence number.
    bool operator >(const unsigned short & seqNum)const;
    
    /// operator < <br/>
    /// true if entries have same sender and left entry has smaller sequence number that right entry.
    bool operator <(const HistoryEntry & other)const;
    
    uint8_t sender()const;
    unsigned short sequenceNumber()const;
};

#endif
