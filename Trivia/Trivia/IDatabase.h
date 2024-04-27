#pragma once

#include <string>

using std::string;


class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool open() = 0;
	virtual bool close() = 0;

	virtual int doesUserExist(string) = 0;
	virtual int doesPasswordMatch(string, string) = 0;
	virtual int addNewUser(string, string, string) = 0;
};
