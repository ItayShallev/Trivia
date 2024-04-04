#pragma once
#include "IRequestHandler.h"
#include <vector>

using std::vector;

typedef vector<unsigned char> Buffer;

enum RequestId
{
	burp
};

struct RequestInfo
{
	Buffer response;
	RequestId id;
};


struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
};
