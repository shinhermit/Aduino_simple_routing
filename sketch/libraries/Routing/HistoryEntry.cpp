#include "HistoryEntry.h"
#include <stdlib.h>
#include <CommonValues.h>

HistoryEntry::HistoryEntry(const unsigned long & sender, const unsigned short & seqNum, const unsigned long & timeStamp)
  :_sender(sender),
  _seqNum(seqNum),
  _timeStamp(timeStamp),
  previous(NULL),
  next(NULL)
{}

HistoryEntry::HistoryEntry(const HistoryEntry & other)
  :_sender(other._sender),
  _seqNum(other._seqNum),
  _timeStamp(other._timeStamp),
  previous(other.previous),
  next(other.next)
{}

void HistoryEntry::update(const unsigned short & seqNum,
			  const unsigned long & timeStamp)
{
  HistoryEntry other(_sender, seqNum, timeStamp);

  if(other > *this)
  {
    _seqNum = seqNum;
    _timeStamp = timeStamp;
  }
}

bool HistoryEntry::operator==(const HistoryEntry & other)const
{
  return (_sender == other._sender
	  && _seqNum == other._seqNum
	  && _timeStamp == other._timeStamp);
}

bool HistoryEntry::operator >(const HistoryEntry & other)const
{
  unsigned long delay = other._timeStamp - _timeStamp;

  return (_sender == other._sender
	  && other._seqNum <= _seqNum
	  && delay < CommonValues::Routing::DELAY_LIMIT);
}

bool HistoryEntry::operator <(const HistoryEntry & other)const
{
  unsigned long delay = other._timeStamp - _timeStamp;

  boolean greaterSeq = (other._seqNum > _seqNum);
  boolean hasBeenResetted = (other._seqNum <= _seqNum
			     && delay > CommonValues::Routing::DELAY_LIMIT);

  return (greaterSeq || hasBeenResetted);
}

unsigned long HistoryEntry::sender()const
{
  return _sender;
}

unsigned short HistoryEntry::sequenceNumber()const
{
  return _seqNum;
}

unsigned long HistoryEntry::timeStamp()const
{
  return _timeStamp;
}

String HistoryEntry::toString()const
{
  char sender[9];
  sprintf(sender, "%08lX", _sender);

  return
    String("HistoryEntry {")
    + String("sender: ") + String(sender)
    + String("seqNum: ") + String(_seqNum)
    + String("timestamp: ") + _timeStamp
    + String("}");
}
