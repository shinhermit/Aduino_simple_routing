#include <stdlib.h>
#include "HistoryEntry.h"

HistoryEntry::HistoryEntry(const uint8_t & sender, const unsigned short & seqNum)
  :_sender(sender),
  _seqNum(seqNum),
  previous(NULL),
  next(NULL)
{}

void HistoryEntry::update(const unsigned short & seqNum)
{
  if(seqNum > _seqNum
      || (seqNum == 0 && _seqNum==255))
  {
    _seqNum = seqNum;
  }
}

bool HistoryEntry::operator==(const HistoryEntry & other)const
{
  return (_sender == other._sender && _seqNum == other._seqNum);
}

bool HistoryEntry::operator >(const HistoryEntry & other)const
{
  return (_sender == other._sender &&
           ( _seqNum > other._seqNum || (_seqNum == 0 && other._seqNum==255) ));
}

bool HistoryEntry::operator >(const unsigned short & seqNum)const
{
  return ( _seqNum > seqNum || (_seqNum == 0 && seqNum==255) );
}

bool HistoryEntry::operator <(const HistoryEntry & other)const
{
  return !operator==(other) && !operator>(other);
}

uint8_t HistoryEntry::sender()const
{
  return _sender;
}

unsigned short HistoryEntry::sequenceNumber()const
{
  return _seqNum;
}

