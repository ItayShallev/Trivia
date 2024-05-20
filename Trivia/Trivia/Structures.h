#pragma once

#include <string>
#include <vector>
#include <ctime>
#include "Constants.h"
#include "IRequestHandler.h"
#include "json.hpp"

// Forward declarations
struct RoomData;
class IRequestHandler;

using std::string;
using std::vector;
using nlohmann::json;

typedef unsigned int uint;


// ******************* REQUESTS STRUCTURES *******************
struct LoginRequest
{
	string username;
	string password;
};


struct SignupRequest
{
	string username;
	string password;
	string mail;
};


struct GetPlayersInRoomRequest
{
	uint roomID;
};


struct JoinRoomRequest
{
	uint roomID;
};


struct CreateRoomRequest
{
	string roomName;
	uint maxPlayers;
	uint questionCount;
	uint answerTimeout;
};


struct CheckIfUserExistsRequest
{
	string username;
};



// ******************* RESPONSE STRUCTURES *******************
struct ErrorResponse
{
	string message = "ERROR";
};
void to_json(json& j, const ErrorResponse& response);


struct LoginResponse
{
	uint status = 1;
};
void to_json(json& j, const LoginResponse& response);


struct SignupResponse
{
	uint status = 1;
};
void to_json(json& j, const SignupResponse& response);


struct LogoutResponse
{
	uint status = 1;
};
void to_json(json& j, const LogoutResponse& response);


struct GetRoomsResponse
{
	uint status = 1;
	vector<RoomData> rooms;
};
void to_json(json& j, const GetRoomsResponse& response);


struct GetPlayersInRoomResponse
{
	vector<string> players;
};
void to_json(json& j, const GetPlayersInRoomResponse& response);


struct GetHighScoreResponse
{
	uint status = 1;
	vector<string> statistics;
};

void to_json(json& j, const GetHighScoreResponse& response);


struct GetPersonalStatsResponse
{
	uint status = 1;
	vector<string> statistics;
};
void to_json(json& j, const GetPersonalStatsResponse& response);


struct JoinRoomResponse
{
	uint status = 1;
};
void to_json(json& j, const JoinRoomResponse& response);


struct CreateRoomResponse
{
	uint status = 1;
};
void to_json(json& j, const CreateRoomResponse& response);


struct CheckIfUserExistsResponse
{
	bool exists = true;
	CheckIfUserExistsResponse(bool _exists) : exists(_exists) {}
};
void to_json(json& j, const CheckIfUserExistsResponse& response);



// ************************** OTHERS *************************
typedef vector<unsigned char> Buffer;


struct RequestInfo
{
	Buffer buffer;
	RequestId id;
	time_t ReceivalTime;
};


struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
};


struct RoomData
{
	uint id;
	string name;
	uint maxPlayers;
	uint numOfQuestionsInGame;
	uint timePerQuestion;
	RoomState roomState;
};
void to_json(json& j, const RoomData& response);
