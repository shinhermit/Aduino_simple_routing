#include "HistoryEntry.h"
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

unsigned long HistoryEntry::sender()const
{
  return _sender;
}

unsigned short HistoryEntry::sequenceNumber()const
{
  return _seqNum;
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
