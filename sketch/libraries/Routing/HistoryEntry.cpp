#include "HistoryEntry.h"
#include <stdlib.h>
#include <CommonValues.h>
#include <math.h>

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
    _seqNum = seqNum;
    _timeStamp = timeStamp;
}

bool HistoryEntry::isDuplicateOf(const HistoryEntry & other)const
{
  return _sender == other._sender
	  && _duplicates(other);
}

bool HistoryEntry::isNewerThan(const HistoryEntry & other)const
{
  return _sender == other._sender
    && _newerThan(other);
}

bool HistoryEntry::isOlderThan(const HistoryEntry & other)const
{
  return _sender == other._sender
    && _olderThan(other);
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

bool HistoryEntry::_duplicates(const HistoryEntry & other)const
{
  return 
    !_olderThan(other)
    && !_newerThan(other);
}

bool HistoryEntry::_newerThan(const HistoryEntry & other)const
{
  unsigned long delay = abs(other._timeStamp - _timeStamp);

  bool greaterSeq = _seqNum > other._seqNum;
  bool afterReset = (_seqNum <= other._seqNum
		     && delay > CommonValues::Routing::DELAY_LIMIT);

  return greaterSeq || afterReset;
}

bool HistoryEntry::_olderThan(const HistoryEntry & other)const
{
  unsigned long delay = abs(other._timeStamp - _timeStamp);

  return _seqNum < other._seqNum
	 && delay <= CommonValues::Routing::DELAY_LIMIT;
}

String HistoryEntry::toString()const
{
  char sender[9];
  sprintf(sender, "%08lX", _sender);

  return
    String("HistoryEntry {")
    + String("sender: ") + String(sender)
    + String(", seqNum: ") + String(_seqNum)
    + String(", timestamp: ") + _timeStamp
    + String("}");
}
