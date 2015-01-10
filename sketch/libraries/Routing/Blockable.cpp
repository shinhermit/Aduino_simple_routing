#include "Blockable.h"

#include <SoftwareSerial.h>

Blockable::Blockable()
  :_isBlocked(false),
   _blockStart(0),
   _blockLen(0)
{}

void Blockable::block(const unsigned long & blockLenMillis)
{
  if(!_isBlocked)
  {
    _blockStart = millis();

    block();

    _blockLen = blockLenMillis;
  }
}

void Blockable::block()
{
  _isBlocked = true;
}

void Blockable::unblock()
{
  _isBlocked = false;
  _blockStart = 0;
  _blockLen = 0;
}


void Blockable::update()
{
  unsigned long now = millis();

Serial.println("update");
  if(!_isBlocked)
  {
    onUpdate();
  }
  else
  {
    if(_blockLen != 0
       && now > _blockStart)
    {
      if(now - _blockStart >= _blockLen)
      {
	unblock();
      }
    }
  }
}

bool Blockable::isBlocked()const
{
  return _isBlocked;
}
