#ifndef ALERT_H
#define ALERT_H

/**
 * Represents an alert which is is to be sent to the sink node.
 * <p>An alert encapsulates the type of sensor which issues a value, and
 * the value issued.</p>
 * <p>Reminder: in this application, all alerts are sent to a single
 * node, called the sink node.</p>
 */
class Alert
{
 private:
  /// The type of the alert (actually, the type of sensor).
  unsigned short _alertType;

  /// The value read from the sensor.
  float _sensorValue;

 public:
  /**
   * Creates an alert concerning a certain type of sensor and a value issued by this sensor.
   * \param alertType the type of sensor involved.
   * \param sensorValue the value issued by the sensor.
   */
  Alert(const unsigned short & alertType,
          const float & sensorValue);

  /**
   * Creates an alert concerning a certain type of sensor and a value issued by this sensor.
   * \param sensorValue the value issued by the sensor.
   */
  Alert(const float & sensorValue);

  /**
   * Creates an alert concerning a certain type of sensor and a value issued by this sensor.
   */
  Alert();
  
  /**
   * Copy constructor.
   */
  Alert(const Alert & Alert);
  
  /**
   * Operator =
   */
  Alert & operator=(const Alert & other);
  
  /**
   * Provides the type of sensor which issued the value of the alert.
   * \return  the type of sensor which issued the value of the alert.
   */
  unsigned short getAlertType()const;

  /**
   * Provides the value of this alert.
   * \return the value of this alert.
   */
  float getSensorValue()const;
  
  /**
   * Defines the type of sensor which issued the value of the alert.
   * \param alertType the type of sensor which issued the value of the alert.
   */
  void setAlertType(const unsigned short & alertType);

  /**
   * Defines the type of sensor which issued the value of the alert.
   * \param sensorValue the value of this alert.
   */
  void setSensorValue(const float & sensorValue);
};

#endif

