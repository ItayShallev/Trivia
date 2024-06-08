#pragma once

#include <string>
#include <vector>
#include "Question.h"

using std::string;
using std::vector;


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
	virtual int getNumOfCorrectAnswers(const string& username) = 0;
	virtual int getNumOfTotalAnswers(const string& username) = 0;
	virtual int getNumOfPlayerGames(const string& username) = 0;
	virtual int getPlayerScore(const string& username) = 0;

	virtual vector<string> getUserStatistics(const string& username) = 0;
	virtual vector<string> getHighScores() = 0;

	virtual Question getQuestion(const int& questionId) = 0;
	virtual vector<Question> getRandomQuestions(const int& numberOfQuestions) = 0;
};
