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
  assert(entry11 > entry10);
  assert(entry21 > entry20);
  assert(entry31 > entry30);
  assert(entry41 > entry40);
  
  assert(entry12 > entry10);
  assert(entry22 > entry20);
  assert(entry32 > entry30);
  assert(entry42 > entry40);
  
  assert(entry13 < entry10);
  assert(entry23 < entry20);
  assert(entry33 < entry30);
  assert(entry43 < entry40);
  
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

