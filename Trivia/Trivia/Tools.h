#pragma once
#include "IRequestHandler.h"
#include <vector>
#include <ctime>


using std::vector;
using std::time_t;

typedef vector<unsigned char> Buffer;

enum RequestId
{
	LoginRequestId = 0,
	SignupRequestId = 1
};

enum ResponseId
{
	LoginResponseId = 0,
	SignupResponseId = 1,
	ErrorResponseId = 2
};

typedef struct RequestInfo
{
	Buffer response;
	RequestId id;
	time_t ReceivalTime;
} RequestInfo;


typedef struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
} RequestResult;