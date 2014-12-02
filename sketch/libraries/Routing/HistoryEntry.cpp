#include "HistoryEntry.h"
#include <stdlib.h>
#include <CommonValues.h>

HistoryEntry::HistoryEntry(const uint8_t & sender, const unsigned short & seqNum)
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
  const unsigned short maxSeq = CommonValues::Message::SEQUENCE_NUMBER_MOD - 1;

  if(seqNum > _seqNum
      || (seqNum == 0 && _seqNum == maxSeq))
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
  const unsigned short maxSeq = CommonValues::Message::SEQUENCE_NUMBER_MOD - 1;

  return (_sender == other._sender &&
           ( _seqNum > other._seqNum || (_seqNum == 0 && other._seqNum == maxSeq) ));
}

bool HistoryEntry::operator >(const unsigned short & seqNum)const
{
  const unsigned short maxSeq = CommonValues::Message::SEQUENCE_NUMBER_MOD - 1;

  return ( _seqNum > seqNum || (_seqNum == 0 && seqNum == maxSeq) );
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

