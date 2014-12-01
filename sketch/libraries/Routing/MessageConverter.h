#ifndef MESSAGE_CONVERTER_H
#define MESSAGE_CONVERTER_H

#include "String.h"
#include "Message.h"

class MessageConverter
{
  private:
    static unsigned short currentToken;
    
    static void getTokens(const String & mess, const String & seperator,
                          const unsigned short nbTokens, String * fillMe);

    static String floatToString(const float & val);
    
  public:
  
    static String serialize(const Message & mess);
    
    static Message* parse(const String & mess);
};

#endif

