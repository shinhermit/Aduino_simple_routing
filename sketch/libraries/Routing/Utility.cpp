#include "Utility.h"

#include <stdlib.h> /* strtof */

int Utility::Board::sendAtCommand(XBee & xbee,
			 AtCommandRequest & atRequest,
			 AtCommandResponse & atResponse)
{
  int statusCode = 0;
  
  // send the command
  xbee.send(atRequest);

  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000))
  {
    // should be an AT command response
    if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE)
    {
      xbee.getResponse().getAtCommandResponse(atResponse);

      if (atResponse.isOk())
      {
        statusCode = 1;
      } 
      else
      {
        statusCode = -1;
      }
    }
    else
    {
      statusCode = -2;
    }   
  }
  else
  {
    // at command failed
    if (xbee.getResponse().isError())
    {
      statusCode = 0;
    } 
    else
    {
      statusCode = -3;
    }
  }
  
  return statusCode;
}

String Utility::Board::getMACPart(XBee & xbee, uint8_t cmd[])
{
   int reqStatus;
   
  AtCommandRequest atRequest = AtCommandRequest();
  AtCommandResponse atResponse = AtCommandResponse();

  // set command to get high/low part of MAC address
  atRequest.setCommand(cmd);

  do
  {
    reqStatus = sendAtCommand(xbee, atRequest, atResponse);
    Serial.println("   ");
    Serial.println(reqStatus);
  }
  while (reqStatus <= 0);
 
  char addr_part[8];
  String addr = "";
  
  // get each value, convert into string and append to the addr
  for (int i = 0; i < atResponse.getValueLength(); i++)
  {
    sprintf(addr_part, "%lX", (unsigned long)(atResponse.getValue()[i]));
    
    if (atResponse.getValue()[i]<=0xF) 
      addr += 0;
        
    addr += addr_part;
  }

  return addr;
}

String Utility::Board::getMACLowPart(XBee & xbee)
{
  uint8_t cmd[] = {'S','L'};

  return Utility::Board::getMACPart(xbee, cmd);
}

String Utility::Board::getMACHighPart(XBee & xbee)
{
  uint8_t cmd[] = {'S','H'};

  return Utility::Board::getMACPart(xbee, cmd);
}

String Utility::Board::getMACAddress(XBee & xbee)
{
  return
    Utility::Board::getMACHighPart(xbee)
    + Utility::Board::getMACLowPart(xbee);
}

float Utility::Convert::stringToFloat(String value)
{
  char strVal[31];
  value.toCharArray(strVal, 30);

  return atof(strVal);
}

String Utility::Convert::floatToString(float value)
{
  int ent, dec;

  ent = int(value);
  dec = int((value - ent)*1000);

  return String("")+ent+String(".")+dec;
}
