#include "HistoryEntry.h"
#include <CommonValues.h>
#include <math.h> // for abs()

HistoryEntry::HistoryEntry(const unsigned long & sender, const unsigned short & seqNum)
  :_sender(sender),
  _seqNum(seqNum),
  previous(NULL),
  next(NULL)
{}

HistoryEntry::HistoryEntry(const HistoryEntry & other)
  :_sender(other._sender),
  _seqNum(other._seqNum),
  previous(other.previous),
  next(other.next)
{}

void HistoryEntry::update(const unsigned short & seqNum)
{
    _seqNum = seqNum;
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

bool HistoryEntry::_duplicates(const HistoryEntry & other)const
{
  return _seqNum == other._seqNum;
}

bool HistoryEntry::_newerThan(const HistoryEntry & other)const
{
  bool greaterSeq = _seqNum > other._seqNum;

  bool tooGreatOfADiff = abs(_seqNum - other._seqNum) > CommonValues::Routing::MAX_SEQ_DIFF;

  return greaterSeq || tooGreatOfADiff;
}

bool HistoryEntry::_olderThan(const HistoryEntry & other)const
{
  return !_duplicates(other) && !_newerThan(other);
}

long double HistoryEntry::_unsignedDiff(const unsigned long & x,
			 const unsigned long & y)const
{
  return (x > y) ? x - y : y - x;
  //return (x > y) ? x - y : -(y - x);
}

String HistoryEntry::toString()const
{
  char sender[9];
  sprintf(sender, "%08lX", _sender);

  return
    String("HistoryEntry {")
    + String("sender: ") + String(sender)
    + String(", seqNum: ") + String(_seqNum)
    + String("}");
}
