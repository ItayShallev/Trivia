#pragma once

#include <string>

using std::string;


class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool open() = 0;
	virtual bool close() = 0;

	virtual bool doesUserExist(const string& username) = 0;
	virtual bool doesPasswordMatch(const string& username, const string& password) = 0;
	virtual bool addNewUser(const string& username, const string& password, const string& mail) = 0;
};
