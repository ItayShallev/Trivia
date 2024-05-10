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

	vector<string> getHighScore();
	vector<string> getUserStatistics(const string& username);

private:
	IDatabase* m_database;
};
