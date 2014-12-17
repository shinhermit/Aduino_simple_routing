#include "MessageHistory.h"

#include <SoftwareSerial.h>

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
			 const unsigned short & seqNum,
			 const unsigned long & timeStamp)
{
  HistoryEntry *currentEntry, *incoming;
  bool newValue = true;

  incoming = new HistoryEntry(sender, seqNum, timeStamp);

  if(_first == NULL)
  {
    _first = incoming;
    _last = _first;

    //Serial.println("History is empty => new message !");
  }
  else
  {
    currentEntry = findEntry(sender);
    
    if(currentEntry != NULL)
    {
      if(incoming->isNewerThan(*currentEntry))
      {
        currentEntry->update(seqNum, timeStamp);

	//Serial.println("incoming entry found greater => new message !");
      }
      else
      {
        newValue = false;
	//Serial.println("incoming entry not found greater => old message !");
      }

      delete incoming;
    }
    else
    {
      _last->next = incoming;
      _last->next->previous = _last;
      _last = _last->next;

      //Serial.println("No current entry found => new message !");
    }
  }

  return newValue;
}

bool MessageHistory::add(const unsigned long & sender,
			 const unsigned short & seqNum)
{
  add(sender, seqNum, millis());
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

