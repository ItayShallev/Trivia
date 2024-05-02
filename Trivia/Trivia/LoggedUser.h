#pragma once

#include <string>

using std::string;


class LoggedUser
{
public:
	LoggedUser(const string& username);
	
	string getUserName() const;

private:
	string m_username;
};
