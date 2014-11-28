#include "SourceNode.h"

SourceNode::SourceNode(const uint8_t & myAddress, const unsigned short & sensorPin)
  :_myAddress(myAddress),
  _sensorPin(sensorPin)
{}

SourceNode::SourceNode()
  :_myAddress(0),
  _sensorPin(0)
{}

void SourceNode::initialize(const uint8_t & myAddress, const unsigned short & sensorPin)
{
  _myAddress = myAddress;
  _sensorPin = sensorPin;
}

void SourceNode::processMessages()const
{
}

float SourceNode::readSensor()const
{
  return 0;
}

void SourceNode::sendAlert(const Alert & alert)const
{
}

