#include <XBee.h>
#include <SoftwareSerial.h>

String getOwnMacAddress(XBee & xbee);
int sendAtCommand(XBee & xbee,
                  AtCommandRequest & atRequest,
                  AtCommandResponse & atResponse);

void setup()
{
  XBee xbee = XBee();

  xbee.begin(38400);
  Serial.begin(38400);

  String addr = getMacAddress(xbee);

  Serial.print("Arduino -mac:");
  Serial.println(addr);
	       
}

void loop()
{
}

String getMacAddress(XBee & xbee)
{
   int reqStatus;
   
  AtCommandRequest atRequest = AtCommandRequest();
  AtCommandResponse atResponse = AtCommandResponse();
  
  // serial high
  uint8_t shCmd[] = {'S','H'};
  // serial low
  uint8_t slCmd[] = {'S','L'};

  // set command to SH to get high part of MAC address
  atRequest.setCommand(shCmd);

  do
  {
    reqStatus = sendAtCommand(xbee, atRequest, atResponse);
    Serial.println(reqStatus);
  }
  while (reqStatus <= 0);
 
  char adr_part[8];
  String adr = "";
  
  // get each value, convert into string and append to the adr
  for (int i = 0; i < atResponse.getValueLength(); i++)
  {
    sprintf(adr_part, "%lX", (unsigned long)(atResponse.getValue()[i]));
    
    if (atResponse.getValue()[i]<=0xF) 
      adr += 0;
        
    adr += adr_part;
  } 

  // set command to SL to get low part of MAC address
  atRequest.setCommand(slCmd);
  
  do
  {
    reqStatus = sendAtCommand(xbee, atRequest, atResponse);
    Serial.println(reqStatus);
  }
  while (reqStatus <= 0);
  
  for (int i = 0; i < atResponse.getValueLength(); i++)
  {
    sprintf(adr_part, "%lX", (unsigned long)(atResponse.getValue()[i]));
    
    if (atResponse.getValue()[i]<=0xF) 
      adr += 0;
        
    adr += adr_part;
  } 

  return adr;
}

// used here to sens AT command to the Xbee to get information such as the MAC address
int sendAtCommand(XBee & xbee,
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
