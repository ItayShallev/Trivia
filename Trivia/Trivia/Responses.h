#pragma once
#include <string>

using std::string;


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
	string message;
};
