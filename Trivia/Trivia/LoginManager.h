#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>

using std::vector;


class LoginManager
{
public:
	LoginManager(IDatabase* database, const vector<LoggedUser>& loggedUsers);

	bool signup(const string& username, const string& password, const string& mail) const;
	bool login(const string& username, const string& password);
	bool logout(const string& username);
	bool doesUserExist(const string& username);

private:
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;
};
