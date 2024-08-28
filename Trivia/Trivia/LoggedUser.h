#pragma once

#include <string>
#include "Constants.h"


using std::string;


class LoggedUser
{
public:
	LoggedUser(const string& username, const UserStatus& userStatus);

	string getUserName() const;
	UserStatus getUserStatus() const;

	void setUserStatus(const UserStatus& newUserStatus);

	bool operator==(const LoggedUser& other) const;
	bool operator==(const LoggedUser* other) const;

private:
	string m_username;
	UserStatus m_userStatus;
};
