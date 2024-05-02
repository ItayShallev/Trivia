#pragma once

#include "IDatabase.h"
#include "sqlite3.h"


class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase(const string& databaseName);
	~SqliteDatabase() override;

	template<typename funcPtr>
	bool executeSqlStatement(const std::string& statement, const funcPtr callbackFunction, void* callbackParam);

	bool initDatabase();

	virtual bool open() override;
	virtual bool close() override;

	// SQL Queries
	static int doesUserExistsCallback(void* data, int argc, char** argv, char** azColName);
	virtual bool doesUserExist(const string& username) override;

	static int doesPasswordMatchCallback(void* data, int argc, char** argv, char** azColName);
	virtual bool doesPasswordMatch(const string& username, const string& password) override;

	virtual bool addNewUser(const string& username, const string& password, const string& mail) override;

private:
	sqlite3* _db;
	string _databaseName;
};
