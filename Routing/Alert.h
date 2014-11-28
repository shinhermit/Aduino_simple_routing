#ifndef ALERT_H
#define ALERT_H

class Alert
{
 private:
  unsigned short _alertType;
  float _sensorValue;

 public:
  Alert(const unsigned short & alertType,
          const float & sensorValue);

  Alert(const float & sensorValue);
  Alert();
  
  Alert(const Alert & Alert);
  
  Alert & operator=(const Alert & other);
  
  unsigned short getAlertType()const;
  float getSensorValue()const;
  
  void setAlertType(const unsigned short & alertType);
  void setSensorValue(const float & sensorValue);
};

#endif

