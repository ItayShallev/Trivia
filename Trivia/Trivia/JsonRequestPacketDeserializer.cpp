#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include "Constants.h"


using json = nlohmann::json;
using std::stoi;


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buff)
{
    // get the message part of the buffer
    string message = getMessageFromBuffer(buff);

    // get the json data
    json data = json::parse(message);

    // create the request
    LoginRequest newLoginRequest = { data["username"], data["password"] };

    // return the request
    return newLoginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer buff)
{
    // get the message part of the buffer
    string message = getMessageFromBuffer(buff);

    // get the json data
    json data = json::parse(message);

    // create the request
    SignupRequest newSignupRequest = {
    	data["username"],
    	data["password"],
    	data["mail"] };

    
    // return the request
    return newSignupRequest;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(Buffer buff)
{
    // get the message part of the buffer
    string message = getMessageFromBuffer(buff);

    // get the json data
    json data = json::parse(message);

    // create the request
    GetPlayersInRoomRequest newGetPlayersInRoomRequest = { data["roomId"] };

    // return the request
    return newGetPlayersInRoomRequest;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(Buffer buff)
{
    // get the message part of the buffer
    string message = getMessageFromBuffer(buff);

    // get the json data
    json data = json::parse(message);

    // create the request
    JoinRoomRequest newJoinRoomRequest = { data["roomID"] };

    // return the request
    return newJoinRoomRequest;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(Buffer buff)
{
    // get the message part of the buffer
    string message = getMessageFromBuffer(buff);

    // get the json data
    json data = json::parse(message);

    // create the request
    CreateRoomRequest newCreateRoomRequest = {
    	data["roomName"],
    	data["maxPlayers"] ,
    	data["questionCount"],
    	data["answerTimeout"]
    };

    // return the request
    return newCreateRoomRequest;
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
