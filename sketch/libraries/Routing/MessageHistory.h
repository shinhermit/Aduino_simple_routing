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
    /// Deletes HistoryEntry linked list.
    ~MessageHistory();
    
    /// Adds an entry to the history.
    /// <p>If no entry related to the sender exists, the entry is added.<br/>
    /// If an entry already exists:
    /// <ul>
    ///   <li>if the comparison with the existing entry shows a newer message, the entry is added;</li>
    ///   <li>otherwise, the addition is ignored.</li>
    /// </ul>
    /// </p>
    /// \param sender the suffix of the address of the sender of the message which is to taken into accout in the history.
    /// \param seqNum the sequence number of the message.
    /// \param timeStamp the time at which the message arrived.
    /// \return true if an entry is actually added to the history, false if it has been ignored.
    bool add(const unsigned long & sender,
	     const unsigned short & seqNum,
	     const unsigned long & timeStamp);
    
    /// Adds an entry to the history.
    /// <p>If no entry related to the sender exists, the entry is added.<br/>
    /// If an entry already exists:
    /// <ul>
    ///   <li>if the comparison with the existing entry shows a newer message, the entry is added;</li>
    ///   <li>otherwise, the addition is ignored.</li>
    /// </ul>
    /// </p>
    /// <p> When a new entry is added to the history, it is marked with the current timestamp</p>
    /// \param sender the suffix of the address of the sender of the message which is to taken into accout in the history.
    /// \param seqNum the sequence number of the message.
    /// \return true if an entry is actually added to the history, false if it has been ignored.
    bool add(const unsigned long & sender,
	     const unsigned short & seqNum);
    
    /// Deletes an entry from the history.
    /// \param sender the suffix of the address of the sender of the message which is to taken into accout in the history.
    void remove(const unsigned long & sender);
    
    /// Retrives the history entry of the sender.
    /// \param sender the suffix of the address of the sender of the message which is to taken into accout in the history.
    /// \return the corresponding entry if found, null otherwise.
    HistoryEntry * findEntry(const unsigned long & sender)const;
    
  private:
    /// The first history entry of the linked-list history entries.
    HistoryEntry * _first;
    /// The last history entry of the linked-list history entries.
    HistoryEntry * _last;
};

#endif
