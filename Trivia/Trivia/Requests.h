#pragma once

#include <string>

using std::string;


struct LoginRequest
{
	string userName;
	string password;
};


struct SignupRequest
{
	string username;
	string password;
	string email;
};
