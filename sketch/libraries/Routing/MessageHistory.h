#ifndef MESSAGE_HISTORY_H
#define MESSAGE_HISTORY_H

#include "HistoryEntry.h"

/**
* Stores the last message from each source.
*/
class MessageHistory
{
  public:    
    /// Constructor.
    MessageHistory();
    
    /// Destructor.
    /// Delete HistoryEntry linked list.
    ~MessageHistory();
    
    /// Adds an entry to the history.
    /// If no entry related to the sender exists, the entry is added.<br/>
    /// If an entry already exists:
    /// <ul>
    ///   <li>if the sequence number shows a newer message, the old entry is updated;</li>
    ///   <li>otherwise, the addition is ignored.</li>
    /// </ul>
    bool add(const unsigned long & sender, const unsigned short & seqNum);
    
    /// Deletes an entry from the history.
    void remove(unsigned long sender);
    
    /// Tells whether the history contains an entry for
    /// the given source with the given sequence number or not.
    bool contains(unsigned long sender, unsigned short seqNum)const;
    
    /// Retrives the history entry of the sender.
    /// null is return if no entry found.
    HistoryEntry * findEntry(unsigned long sender)const;
    
  private:
    /// The first history entry of the linked-list history entries.
    HistoryEntry * _first;
    /// The last history entry of the linked-list history entries.
    HistoryEntry * _last;
};

#endif
