#include "Alert.h"
#include "CommonValues.h"

Alert::Alert(const unsigned short & alertType,
        const float & sensorValue)
 :_alertType(alertType),
  _sensorValue(sensorValue)
{}

Alert::Alert(const float & sensorValue)
 :_alertType(CommonValues::Alert::DEFAULT_ALERT_TYPE),
  _sensorValue(sensorValue)
{}

Alert::Alert()
 :_alertType(CommonValues::Alert::DEFAULT_ALERT_TYPE),
  _sensorValue(0)
{}

  
Alert::Alert(const Alert & other)
 :_alertType(other._alertType),
  _sensorValue(other._sensorValue)
{}

Alert & Alert::operator=(const Alert & other)
{
  _alertType = other._alertType;
  _sensorValue = other._sensorValue;
  
  return *this;
}

unsigned short Alert::getAlertType()const
{
  return _alertType;
}

float Alert::getSensorValue()const
{
  return _sensorValue;
}

void Alert::setAlertType(const unsigned short & alertType)
{
  _alertType = alertType;
}

void Alert::setSensorValue(const float & sensorValue)
{
  _sensorValue = sensorValue;
}

String Alert::toString()const
{
  return String("Alert {type: ")
         +_alertType
         +String(", value: ")
         +_sensorValue+String("}");
}
