#pragma once

#include <string>
#include <vector>
#include "GameStructures.h"
#include "LoggedUser.h"
#include "Question.h"


using std::string;
using std::vector;
using std::map;
using std::shared_ptr;


class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool open() = 0;
	virtual bool close() = 0;

	virtual bool doesUserExist(const string& username) = 0;
	virtual bool doesPasswordMatch(const string& username, const string& password) = 0;
	virtual bool addNewUser(const string& username, const string& password, const string& mail) = 0;

	virtual float getPlayerAverageAnswerTime(const string& username) = 0;
	virtual uint getNumOfCorrectAnswers(const string& username) = 0;
	virtual uint getNumOfTotalAnswers(const string& username) = 0;
	virtual uint getNumOfPlayerGames(const string& username) = 0;
	virtual uint getPlayerScore(const string& username) = 0;

	virtual HighScoreRow getUserStatistics(const string& username) = 0;
	virtual vector<HighScoreRow> getHighScores() = 0;
	virtual void submitGameStatistics(const map<shared_ptr<LoggedUser>, GameData>& users) = 0;

	virtual vector<Question> getRandomQuestions(const uint& numberOfQuestions) = 0;
};
