#pragma once

#include "IDatabase.h"
#include "sqlite3.h"


class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase(const string& databaseName);
	~SqliteDatabase() override;

	template<typename funcPtr>
	bool executeSqlStatement(const string& statement, const funcPtr callbackFunction, void* callbackParam);

	bool initDatabase();

	virtual bool open() override;
	virtual bool close() override;

	// ********************************************* USERS table queries *********************************************
	static int doesUserExistsCallback(void* data, int argc, char** argv, char** azColName);						  // *
	virtual bool doesUserExist(const string& username) override;												  // *
																												  // *
	static int doesPasswordMatchCallback(void* data, int argc, char** argv, char** azColName);					  // *
	virtual bool doesPasswordMatch(const string& username, const string& password) override;					  // *
																												  // *
	virtual bool addNewUser(const string& username, const string& password, const string& mail) override;		  // *
																												  // *
	static int intCallback(void* data, int argc, char** argv, char** azColName);								  // *
	static int floatCallback(void* data, int argc, char** argv, char** azColName);								  // *
	//****************************************************************************************************************

	// ******************************************* STATISTICS table queries *******************************************
	virtual float getPlayerAverageAnswerTime(const string& username) override;									   // *
	virtual uint getNumOfCorrectAnswers(const string& username) override;										   // *
	virtual uint getNumOfTotalAnswers(const string& username) override;											   // *
	virtual uint getNumOfPlayerGames(const string& username) override;											   // *
	virtual uint getPlayerScore(const string& username) override;												   // *
																												   // *
	virtual vector<string> getUserStatistics(const string& username) override;									   // *
																												   // *
	static int getHighScoresCallback(void* data, int argc, char** argv, char** azColName);						   // *
	virtual vector<string> getHighScores() override;															   // *
	// ****************************************************************************************************************

	// ************************************************* GAME queries *************************************************
	static int getQuestionCallback(void* data, int argc, char** argv, char** azColName);						   // *
	virtual Question getQuestion(const uint& questionId) override;												   // *
	virtual vector<Question> getRandomQuestions(const uint& numberOfQuestions) override;							   // *
	// ****************************************************************************************************************


private:
	sqlite3* _db;
	string _databaseName;
};
