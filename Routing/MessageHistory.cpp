#include <stdlib.h>
#include "MessageHistory.h"

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

void MessageHistory::add(const uint8_t & sender, const unsigned short & seqNum)
{
  HistoryEntry * entry;
  
  if(_first == NULL)
  {
    _first = new HistoryEntry(sender, seqNum);
    _last = _first;
  }
  else
  {
    entry = findEntry(sender);
    
    if(entry != NULL)
    {
      if((*entry) > seqNum)
      {
        entry->update(seqNum);
      }
    }
    else
    {
      _last->next = new HistoryEntry(sender, seqNum);
      _last->next->previous = _last;
      _last = _last->next;
    }
  }
}

void MessageHistory::remove(uint8_t sender)
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

bool MessageHistory::contains(uint8_t sender, unsigned short seqNum)const
{
  HistoryEntry * entry = findEntry(sender);
  
  if(entry == NULL)
  {
    return false;
  }
  else
  {
    return ( (*entry) == HistoryEntry(sender, seqNum) );
  }
}

HistoryEntry * MessageHistory::findEntry(uint8_t sender)const
{
  HistoryEntry * entry = _first;
  bool found = false;
  
  while(entry != NULL && !found)
  {
    found = (entry->sender() == sender);
    
    if(!found)
    {
      entry = entry->next;
    }
  }
  
  return entry;
}

