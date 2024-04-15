#pragma once

#include <string>
#include <vector>
#include <ctime>
#include "Constants.h"
#include "IRequestHandler.h"

using std::string;
using std::vector;


// ******************* REQUESTS STRUCTURES *******************
struct LoginRequest
{
	string userName;	// name
	string password;	// password
};


struct SignupRequest
{
	string username;	// name
	string password;	// password
	string email;		// mail
};




// ******************* RESPONSE STRUCTURES *******************
struct LoginResponse
{
	unsigned int status;
};


struct SignupResponse
{
	unsigned int status;
};


struct ErrorResponse
{
	string message = "ERROR";
};




// ************************** OTHERS *************************
typedef vector<unsigned char> Buffer;


struct RequestInfo
{
	Buffer response;
	RequestId id;
	time_t ReceivalTime;
};


struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
};
