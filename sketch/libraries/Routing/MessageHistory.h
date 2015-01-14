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
    
    /// Tells whether an history entry which represents an incoming message is a duplicate of the history entry which represents the last received message.
    /// \param current the history entry which represents the last received message.
    /// \param incoming the history entry which represents an incoming message.
    /// \return true if incoming represents message which is a duplictate of the message represented by current.
    static bool isDuplicate(
	    const HistoryEntry & current,
	    const HistoryEntry & incoming);
    
    /// Tells whether a sequence number attached to an incoming message is a duplicate of the sequence number which was attached to the last received message.
    /// <p>This method is useful for discovery message, for which senders are meaningless.</p>
    /// \param current the history entry which represents the last received message.
    /// \param incoming the history entry which represents an incoming message.
    /// \return true if incoming is the sequence number of a message which is a duplictate of the last received message.
    static bool isDuplicate(
	    const unsigned long & current,
	    const unsigned long & incoming);
    
    /// Tells whether an history entry which represents an incoming message is newer than the history entry which represents the last received message.
    /// \param current the history entry which represents the last received message.
    /// \param incoming the history entry which represents an incoming message.
    /// \return true if incoming represents message which is newer than the message represented by current.
    static bool isNewer(
	    const HistoryEntry & current,
	    const HistoryEntry & incoming);
    
    /// Tells whether a sequence number attached to an incoming message is newer than the sequence number which was attached to the last received message.
    /// <p>This method is useful for discovery message, for which senders are meaningless.</p>
    /// \param current the history entry which represents the last received message.
    /// \param incoming the history entry which represents an incoming message.
    /// \return true if incoming is the sequence number of a message which is newer the last received message.
    static bool isNewer(
	    const unsigned long & current,
	    const unsigned long & incoming);
    
    /// Tells whether an history entry which represents an incoming message is older than the history entry which represents the last received message.
    /// \param current the history entry which represents the last received message.
    /// \param incoming the history entry which represents an incoming message.
    /// \return true if incoming represents message which is older than the message represented by current.
    static bool isOlder(
	    const HistoryEntry & current,
	    const HistoryEntry & incoming);
    
    /// Tells whether a sequence number attached to an incoming message is older than the sequence number which was attached to the last received message.
    /// <p>This method is useful for discovery message, for which senders are meaningless.</p>
    /// \param current the history entry which represents the last received message.
    /// \param incoming the history entry which represents an incoming message.
    /// \return true if incoming is the sequence number of a message which is older the last received message.
    static bool isOlder(
	    const unsigned long & current,
	    const unsigned long & incoming);
    
  private:
    /// The first history entry of the linked-list history entries.
    HistoryEntry * _first;
    /// The last history entry of the linked-list history entries.
    HistoryEntry * _last;
};

#endif
