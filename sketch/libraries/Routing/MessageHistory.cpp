#include "MessageHistory.h"

#include <SoftwareSerial.h>
#include <CommonValues.h>

MessageHistory::MessageHistory()
  :_first(NULL),
  _last(NULL)
{}

MessageHistory::~MessageHistory()
{
  HistoryEntry *current, *next;
  
  current = _first;
  while(current != NULL)
  {
    next = current->next;
    
    current->previous = NULL;
    current->next = NULL;
    delete current;
  }
}

bool MessageHistory::add(const unsigned long & sender,
			 const unsigned short & seqNum)
{
  HistoryEntry *currentEntry, *incoming;
  bool newValue = true;

  incoming = new HistoryEntry(sender, seqNum);

  if(_first == NULL)
  {
    _first = incoming;
    _last = _first;

  }
  else
  {
    currentEntry = findEntry(sender);
    
    if(currentEntry != NULL)
    {
      if(MessageHistory::isNewer(*currentEntry, *incoming))
      {
        currentEntry->update(seqNum);
      }
      else
      {
        newValue = false;
      }

      delete incoming;
    }
    else
    {
      _last->next = incoming;
      _last->next->previous = _last;
      _last = _last->next;
    }
  }

  return newValue;
}

void MessageHistory::remove(const unsigned long & sender)
{
  HistoryEntry * entry = findEntry(sender);
  
  if(entry != NULL)
  {
    entry->previous->next = entry->next;
    entry->next->previous = entry->previous;
    
    entry->next = NULL;
    entry->previous = NULL;
    
    delete entry;
  }
}

HistoryEntry * MessageHistory::findEntry(const unsigned long & sender)const
{
  
  HistoryEntry * currentEntry = _first;
  HistoryEntry * foundEntry = NULL;
  
  while(currentEntry != NULL
	&& foundEntry == NULL)
  {
    if(currentEntry->sender() == sender)
    {
      foundEntry = currentEntry;
    }
    else
    {
      currentEntry = currentEntry->next;
    }
  }
  
  return foundEntry;
}

bool MessageHistory::isDuplicate(
	    const unsigned long & current,
	    const unsigned long & incoming)
{
  return current == incoming;
}

bool MessageHistory::isNewer(
	    const unsigned long & current,
	    const unsigned long & incoming)
{
  bool isNewer = false;

  if (current != incoming) 
  {
      for (int i = 1; i <= CommonValues::Routing::MAX_LOSS_TOLERANCE && !isNewer; i++)
      {
	isNewer = (
	   ((incoming + i) % 256) == (current % 256));
      }
  }

  return isNewer;
}

bool MessageHistory::isOlder(
	    const unsigned long & current,
	    const unsigned long & incoming)
{
  return
    !MessageHistory::isDuplicate(current, incoming)
    &&
    !MessageHistory::isNewer(current, incoming);
}

bool MessageHistory::isDuplicate(
	    const HistoryEntry & current,
	    const HistoryEntry & incoming)
{
  return
    current.sender() == incoming.sender()
    &&
    MessageHistory::isDuplicate(
	   current.sequenceNumber(),
	   incoming.sequenceNumber());
}

bool MessageHistory::isNewer(
	    const HistoryEntry & current,
	    const HistoryEntry & incoming)
{
  return
    current.sender() == incoming.sender()
    &&
    MessageHistory::isNewer(
	   current.sequenceNumber(),
	   incoming.sequenceNumber());
}

bool MessageHistory::isOlder(
	    const HistoryEntry & current,
	    const HistoryEntry & incoming)
{
  return
    current.sender() == incoming.sender()
    &&
    MessageHistory::isOlder(
	   current.sequenceNumber(),
	   incoming.sequenceNumber());
}
