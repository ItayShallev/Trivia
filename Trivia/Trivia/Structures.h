#pragma once

#include <string>
#include <vector>
#include <ctime>
#include "Constants.h"

class IRequestHandler;
#include "IRequestHandler.h"

using std::string;
using std::vector;


// ******************* REQUESTS STRUCTURES *******************
struct LoginRequest
{
	string username;	// username
	string password;	// password
};


struct SignupRequest
{
	string username;	// username
	string password;	// password
	string email;		// mail
};




// ******************* RESPONSE STRUCTURES *******************
struct LoginResponse
{
	unsigned int status = 1;
};


struct SignupResponse
{
	unsigned int status = 1;
};


struct ErrorResponse
{
	string message = "ERROR";
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


typedef unsigned int uint;
struct RoomData
{
	uint id;
	string name;
	uint maxPlayers;
	uint numOfQuestionsInGame;
	uint timePerQuestion;
	RoomState roomState;
};