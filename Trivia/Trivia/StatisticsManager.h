#pragma once

#include <string>
#include <vector>
#include "IDatabase.h"

using std::string;
using std::vector;


class StatisticsManager
{
public:
	StatisticsManager(IDatabase* database);

	vector<HighScoreRow> getHighScore() const;
	HighScoreRow getUserStatistics(const string& username) const;

	static uint calculatePoints(const double& answerTime, const uint& timePerQuestion, const QuestionDifficulty& difficulty);

private:
	IDatabase* m_database;
};
