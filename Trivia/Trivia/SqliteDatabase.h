#pragma once

#include "IDatabase.h"
#include "sqlite3.h"


using std::pair;
using std::shared_ptr;


class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase(const string& databaseName);
	~SqliteDatabase() override;

	template<typename funcPtr>
	bool executeSqlStatement(const string& statement, const funcPtr callbackFunction, void* callbackParam);

	bool initDatabase();
	static void fetchQuestion();

	virtual bool open() override;
	virtual bool close() override;

	// ********************************************* USERS table queries *********************************************
	static int doesUserExistCallback(void* data, int argc, char** argv, char** azColName);						  // *
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
	static int getUserStatisticsCallback(void* data, int argc, char** argv, char** azColName);					   // *
	virtual HighScoreRow getUserStatistics(const string& username) override;									   // *
																												   // *
	static int getHighScoresCallback(void* data, int argc, char** argv, char** azColName);						   // *
	virtual vector<HighScoreRow> getHighScores() override;														   // *
																												   // *
	void addUserStatisticsRecord(const string& username);													       // *
																												   // *
	void submitUserGameStatistics(const pair<shared_ptr<LoggedUser>, GameData>& user);							   // *
	virtual void submitGameStatistics(const map<shared_ptr<LoggedUser>, GameData>& users) override;				   // *
	// ****************************************************************************************************************

	// ************************************************* GAME queries *************************************************
	bool compileSqliteStatement(sqlite3_stmt*& statement, const string& query) const;							   // *
	virtual vector<Question> processGetQuestionsResults(sqlite3_stmt* statement);								   // *
	virtual vector<Question> getRandomQuestions(const uint& numberOfQuestions) override;						   // *
	// ****************************************************************************************************************

private:
	sqlite3* _db;
	string _databaseName;
};
