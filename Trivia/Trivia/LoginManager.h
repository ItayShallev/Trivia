#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>

using std::vector;
using std::shared_ptr;


class LoginManager
{
public:
	LoginManager(IDatabase* database, const vector<shared_ptr<LoggedUser>>& loggedUsers);

	bool signup(const string& username, const string& password, const string& mail);
	bool login(const string& username, const string& password);
	bool logout(const string& username);
	bool doesUserExist(const string& username) const;

	shared_ptr<LoggedUser> getLoggedUserByUsername(const string& username) const;

private:
	IDatabase* m_database;
	vector<shared_ptr<LoggedUser>> m_loggedUsers;
};
