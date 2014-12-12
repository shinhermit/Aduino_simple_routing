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
//	Serial.println("other sender "+String(other.sender()));
//	Serial.println("other seqNum "+String(other.sequenceNumber()));
//	Serial.println("other timestamp "+String(other.timeStamp()));
	bool isSameSender = _sender == other._sender;
	bool isSameSeqNum = other._seqNum == _seqNum;
	bool isGreaterSeqNum =  _seqNum > other._seqNum;
	bool hasExpiredDelay = delay > CommonValues::Routing::DELAY_LIMIT;

	return isSameSender && (isGreaterSeqNum || hasExpiredDelay);
}
//Returns false in the case
// e1.sender == e2.sender
// and
// delay >= DELAY_LIMIT
// whatever the seqnum
// Should consider message new if delay has expired.



bool HistoryEntry::operator <(const HistoryEntry & other)const
{
	unsigned long delay = other._timeStamp - _timeStamp;

	bool isSameSender = _sender == other._sender;
	bool smallerSeq = (_seqNum < other._seqNum);
	bool hasBeenResetted = (other._seqNum <= _seqNum
			&& delay > CommonValues::Routing::DELAY_LIMIT);

	return isSameSender && (smallerSeq || hasBeenResetted);
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
