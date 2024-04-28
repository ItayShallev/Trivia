#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>

using std::vector;


class LoginManager
{
public:
	LoginManager();

	bool signup(const string& username, const string& password, const string& mail);
	bool login(const string& username, const string& password);
	bool logout(const string& username);

private:
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;
};
