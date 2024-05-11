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

	vector<string> getHighScore() const;
	vector<string> getUserStatistics(const string& username) const;

private:
	IDatabase* m_database;
};
