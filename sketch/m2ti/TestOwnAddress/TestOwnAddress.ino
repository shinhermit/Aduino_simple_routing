
#include <XBee.h>
#include <SoftwareSerial.h>

#include <Utility.h>

void setup()
{
  XBee xbee = XBee();

  xbee.begin(38400);
  Serial.begin(38400);

  String addr = Utility::Board::getMACAddress(xbee);

  Serial.print("Arduino -mac:");
  Serial.println(addr);
}

void loop()
{
}

