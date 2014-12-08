#include "HistoryEntry.h"
#include <stdlib.h>
#include <CommonValues.h>

HistoryEntry::HistoryEntry(const unsigned long & sender, const unsigned short & seqNum, const time_t & timeStamp)
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
			  const time_t & timeStamp)
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
  double delay = difftime(other._timeStamp, _timeStamp);

  return (_sender == other._sender
	  && other._seqNum <= _seqNum
	  && delay < CommonValues::Routing::DELAY_LIMIT);
}

bool HistoryEntry::operator <(const HistoryEntry & other)const
{
  double delay = difftime(other._timeStamp, _timeStamp);

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

time_t timeStamp()const
{
  return _timeStamp;
}
