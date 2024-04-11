#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"

using json = nlohmann::json;

#define DATA_BYTE_LENGTH 4

using std::stoi;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buff)
{
    // get the message part of the buffer
    string message = getMessageFromBuffer(buff);

    // get the json data
    json data = json::parse(message);
    LoginRequest newLoginRequest = { data["name"], data["password"] };


    return newLoginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer buff)
{
    // get the message part of the buffer
    string message = getMessageFromBuffer(buff);

    // get the json data
    json data = json::parse(message);

    SignupRequest newSignupRequest = { data["name"], data["password"], data["mail"] };

    return newSignupRequest;
}

string JsonRequestPacketDeserializer::getMessageFromBuffer(Buffer buff)
{
    string dataLenStr = "";

    // first byte is request code which is irrelevant
    // iterate from 1 to DATA BYTE LENGTH to get the message length
    for (int i = 1; i <= DATA_BYTE_LENGTH; i++)
    {
        // read the current byte
        dataLenStr += buff[i];
    }

    // get the data length
    int dataLength = stoi(dataLenStr);

    // init an empty message string
    string message = "";

    int currentIndex = DATA_BYTE_LENGTH + 1;
    // start reading the message
    for (int i = 0; i < dataLength; ++i)
    {
        // add the current char to the message
        message += buff[currentIndex];
        currentIndex++;
    }

    // return the message
    return message;
}
