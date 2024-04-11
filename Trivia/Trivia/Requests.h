#pragma once

#include <string>

using std::string;


struct LoginRequest
{
	string userName; // name
	string password; // password
};


struct SignupRequest
{
	string username; // name
	string password; // password
	string email; // mail
};
