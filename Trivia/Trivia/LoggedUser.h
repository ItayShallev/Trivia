#pragma once

#include <string>

using std::string;


class LoggedUser
{
public:
	LoggedUser(const string& username);
	string getUserName() const;
	bool operator==(const LoggedUser& other) const;
	bool operator==(const LoggedUser* other) const;

private:
	string m_username;
};
