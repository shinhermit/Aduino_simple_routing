#ifndef MESSAGE_CONVERTER_H
#define MESSAGE_CONVERTER_H

#include "Message.h"

/**
 * Realizes parse/serialize operations on messages.
 */
class MessageConverter
{
  private:
  /// Points the position of the token to be read.
    static unsigned short currentToken;
    
    /**
     * Reads the tokens from the provided string.
     * \param mess the serialized message which is to be parsed.
     * \param nbTokens the number of tokens which are to be read.
     * \param fillMe an array of String objects which will be filled whith the read tokens.
     */
    static void getTokens(const String & mess, const String & seperator,
                          const unsigned short nbTokens, String * fillMe);
    
  public:

    /**
     * Converts a float value to String.
     * \param val the float value which is to be converted.
     * \return the String representation of the provided value.
     */
    static String floatToString(const float & val);

    /**
     * Converts a string representing a float value into this float value.
     * \param val the string representation of a float value which is to be converted.
     * \return the corresponding float value.
     */
    static float stringToFloat(const String & val);
  
    /**
     * Serializes a Message into a String.
     * \param mess the Message which is to be serialized.
     * \return a String representation of the Message.
     */
    static String serialize(const Message & mess);
    
    /**
     * Parses a String which corresponds to a serialized Message into a Message.
     * \param mess the String representation of a Message.
     * \return the paresed Message.
     */
    static Message* parse(const String & mess);
};

#endif

