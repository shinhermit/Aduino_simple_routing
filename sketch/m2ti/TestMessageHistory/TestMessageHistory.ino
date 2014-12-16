#include <XBee.h>
#include <CommonValues.h>
#include <MessageHistory.h>

#include <assert.h>

void setup()
{
  Serial.begin(CommonValues::Routing::XBEE_RATE);
  
  // Originals seq 4
  HistoryEntry entry10(0x407620B1, 4, millis());
  HistoryEntry entry20(0x407620B2, 4, millis());
  HistoryEntry entry30(0x407620B3, 4, millis());
  HistoryEntry entry40(0x407620B4, 4, millis());
  
  // Newer (seq > 4)
  HistoryEntry entry11(0x407620B1, 5, millis());
  HistoryEntry entry21(0x407620B2, 6, millis());
  HistoryEntry entry31(0x407620B3, 7, millis());
  HistoryEntry entry41(0x407620B4, 8, millis());
  
  // Newer (after reset)
  HistoryEntry entry12(0x407620B1, 4, entry10.timeStamp()+CommonValues::Routing::DELAY_LIMIT+1);
  HistoryEntry entry22(0x407620B2, 3, entry20.timeStamp()+CommonValues::Routing::DELAY_LIMIT+2);
  HistoryEntry entry32(0x407620B3, 2, entry30.timeStamp()+CommonValues::Routing::DELAY_LIMIT+3);
  HistoryEntry entry42(0x407620B4, 1, entry40.timeStamp()+CommonValues::Routing::DELAY_LIMIT+4);
  
  // Duplicates same seq' <= seq && delay < max
  HistoryEntry entry13(0x407620B1, 4, entry10.timeStamp()+CommonValues::Routing::DELAY_LIMIT);
  HistoryEntry entry23(0x407620B2, 3, entry20.timeStamp()+CommonValues::Routing::DELAY_LIMIT-1);
  HistoryEntry entry33(0x407620B3, 2, entry30.timeStamp()+CommonValues::Routing::DELAY_LIMIT-2);
  HistoryEntry entry43(0x407620B4, 1, entry40.timeStamp()+CommonValues::Routing::DELAY_LIMIT-3);
  
  /***** TEST COMPARISON OPERATOR ******/
  if(entry11.isNewerThan(entry10))
  {
    Serial.println(entry11.toString()+" is newer than "+entry10.toString()+": ok");
  }
  else
  {
    Serial.println(entry11.toString()+" is newer than "+entry10.toString()+": fail");
  }
  if(entry11.isOlderThan(entry10))
  {
    Serial.println(entry11.toString()+" is older than "+entry10.toString()+": fail");
  }
  else
  {
    Serial.println(entry11.toString()+" is not older than "+entry10.toString()+": ok");
  }
  
  if(entry21.isNewerThan(entry20))
  {
    Serial.println(entry21.toString()+" is newer than "+entry20.toString()+": ok");
  }
  else
  {
    Serial.println(entry21.toString()+" is newer than "+entry20.toString()+": fail");
  }
  if(entry21.isOlderThan(entry20))
  {
    Serial.println(entry21.toString()+" is older than "+entry20.toString()+": fail");
  }
  else
  {
    Serial.println(entry21.toString()+" is not older than "+entry20.toString()+": ok");
  }
  
  if(entry31.isNewerThan(entry30))
  {
    Serial.println(entry31.toString()+" is newer than "+entry30.toString()+": ok");
  }
  else
  {
    Serial.println(entry31.toString()+" is newer than "+entry30.toString()+": fail");
  }
  if(entry31.isOlderThan(entry30))
  {
    Serial.println(entry31.toString()+" is older than "+entry30.toString()+": fail");
  }
  else
  {
    Serial.println(entry31.toString()+" is not older than "+entry30.toString()+": ok");
  }
  
  if(entry41.isNewerThan(entry40))
  {
    Serial.println(entry41.toString()+" is newer than "+entry40.toString()+": ok");
  }
  else
  {
    Serial.println(entry41.toString()+" is newer than "+entry40.toString()+": fail");
  }
  if(entry41.isOlderThan(entry40))
  {
    Serial.println(entry41.toString()+" is older than "+entry40.toString()+": fail");
  }
  else
  {
    Serial.println(entry41.toString()+" is not older than "+entry40.toString()+": ok");
  }
  
  if(entry12.isNewerThan(entry10))
  {
    Serial.println(entry12.toString()+" is newer than "+entry10.toString()+": ok");
  }
  else
  {
    Serial.println(entry12.toString()+" is newer than "+entry10.toString()+": fail");
  }
  if(entry12.isOlderThan(entry10))
  {
    Serial.println(entry12.toString()+" is older than "+entry10.toString()+": fail");
  }
  else
  {
    Serial.println(entry12.toString()+" is not older than "+entry10.toString()+": ok");
  }
  
  if(entry22.isNewerThan(entry20))
  {
    Serial.println(entry22.toString()+" is newer than "+entry20.toString()+": ok");
  }
  else
  {
    Serial.println(entry22.toString()+" is newer than "+entry20.toString()+": fail");
  }
  if(entry22.isOlderThan(entry20))
  {
    Serial.println(entry22.toString()+" is older than "+entry20.toString()+": fail");
  }
  else
  {
    Serial.println(entry22.toString()+" is not older than "+entry20.toString()+": ok");
  }
  
  if(entry32.isNewerThan(entry30))
  {
    Serial.println(entry32.toString()+" is newer than "+entry30.toString()+": ok");
  }
  else
  {
    Serial.println(entry32.toString()+" is newer than "+entry30.toString()+": fail");
  }
  if(entry32.isOlderThan(entry30))
  {
    Serial.println(entry32.toString()+" is older than "+entry30.toString()+": fail");
  }
  else
  {
    Serial.println(entry32.toString()+" is not older than "+entry30.toString()+": ok");
  }
  
  if(entry42.isNewerThan(entry40))
  {
    Serial.println(entry42.toString()+" is newer than "+entry40.toString()+": ok");
  }
  else
  {
    Serial.println(entry42.toString()+" is newer than "+entry40.toString()+": fail");
  }
  if(entry42.isOlderThan(entry40))
  {
    Serial.println(entry42.toString()+" is older than "+entry40.toString()+": fail");
  }
  else
  {
    Serial.println(entry42.toString()+" is not older than "+entry40.toString()+": ok");
  }
  
  if(entry13.isDuplicateOf(entry10))
  {
    Serial.println(entry13.toString()+" is duplicate of "+entry10.toString()+": ok");
  }
  else
  {
    Serial.println(entry13.toString()+" is duplicate of "+entry10.toString()+": fail");
  }
  if(entry13.isOlderThan(entry10))
  {
    Serial.println(entry13.toString()+" is older than "+entry10.toString()+": fail");
  }
  else
  {
    Serial.println(entry13.toString()+" is not older than "+entry10.toString()+": ok");
  }
   if(entry13.isNewerThan(entry10))
  {
    Serial.println(entry13.toString()+" is newer than "+entry10.toString()+": fail");
  }
  else
  {
    Serial.println(entry13.toString()+" is not newer than "+entry10.toString()+": ok");
  }
 
  if(entry23.isOlderThan(entry20))
  {
    Serial.println(entry23.toString()+" is older than "+entry20.toString()+": ok");
  }
  else
  {
    Serial.println(entry23.toString()+" is older than "+entry20.toString()+": fail");
  }
  if(entry23.isNewerThan(entry20))
  {
    Serial.println(entry23.toString()+" is newer than "+entry20.toString()+": fail");
  }
  else
  {
    Serial.println(entry23.toString()+" is not newer than "+entry20.toString()+": ok");
  }
  
  if(entry33.isOlderThan(entry30))
  {
    Serial.println(entry33.toString()+" is older than "+entry30.toString()+": ok");
  }
  else
  {
    Serial.println(entry33.toString()+" is older than "+entry30.toString()+": fail");
  }
  if(entry33.isNewerThan(entry30))
  {
    Serial.println(entry33.toString()+" is newer than "+entry30.toString()+": fail");
  }
  else
  {
    Serial.println(entry33.toString()+" is not newer than "+entry30.toString()+": ok");
  }
  
  if(entry43.isOlderThan(entry40))
  {
    Serial.println(entry43.toString()+" is older than "+entry40.toString()+": ok");
  }
  else
  {
    Serial.println(entry43.toString()+" is older than "+entry40.toString()+": fail");
  }
  if(entry43.isNewerThan(entry40))
  {
    Serial.println(entry43.toString()+" is newer than "+entry40.toString()+": fail");
  }
  else
  {
    Serial.println(entry43.toString()+" is not newer than "+entry40.toString()+": ok");
  }
  
  
  /***** TEST HISTORY MANAGEMENT ******/
  MessageHistory history;
  
  history.add(entry10.sender(), entry10.sequenceNumber(), entry10.timeStamp());
  
  // try exact duplicate
  history.add(entry10.sender(), entry10.sequenceNumber(), entry10.timeStamp());
  
  // Add the others
  history.add(entry20.sender(), entry20.sequenceNumber(), entry20.timeStamp());
  history.add(entry30.sender(), entry30.sequenceNumber(), entry30.timeStamp());
  history.add(entry40.sender(), entry40.sequenceNumber(), entry40.timeStamp());
  
  // Try duplicates 
  history.add(entry13.sender(), entry13.sequenceNumber(), entry13.timeStamp());
  history.add(entry23.sender(), entry23.sequenceNumber(), entry23.timeStamp());
  history.add(entry33.sender(), entry33.sequenceNumber(), entry33.timeStamp());
  history.add(entry43.sender(), entry43.sequenceNumber(), entry43.timeStamp());
  
  // Try newer  (seq' > seq)
  history.add(entry11.sender(), entry11.sequenceNumber(), entry11.timeStamp());
  history.add(entry21.sender(), entry21.sequenceNumber(), entry21.timeStamp());
  history.add(entry31.sender(), entry31.sequenceNumber(), entry31.timeStamp());
  history.add(entry41.sender(), entry41.sequenceNumber(), entry41.timeStamp());
  
  // Try newer  (after reset)
  history.add(entry12.sender(), entry12.sequenceNumber(), entry12.timeStamp());
  history.add(entry22.sender(), entry22.sequenceNumber(), entry22.timeStamp());
  history.add(entry32.sender(), entry32.sequenceNumber(), entry32.timeStamp());
  history.add(entry42.sender(), entry42.sequenceNumber(), entry42.timeStamp());
}

void loop()
{
  
}

