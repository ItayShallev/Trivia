#pragma once

#include <string>
#include <vector>
#include <ctime>
#include "Constants.h"

struct RoomData;
class IRequestHandler;
#include "IRequestHandler.h"

using std::string;
using std::vector;

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



// ******************* RESPONSE STRUCTURES *******************
struct LoginResponse
{
	uint status = 1;
};


struct SignupResponse
{
	uint status = 1;
};


struct ErrorResponse
{
	string message = "ERROR";
};

struct LogoutResponse
{
	uint status = 1;
};

struct GetRoomResponse
{
	uint status = 1;
	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	vector<string> players;
};

struct GetHighScoreResponse
{
	uint status = 1;
	vector<string> statistics;
};

struct GetPersonalStatsResponse
{
	uint status = 1;
	vector<string> statistics;
};

struct JoinRoomResponse
{
	uint status = 1;
};

struct CreateRoomResponse
{
	uint status = 1;
};




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