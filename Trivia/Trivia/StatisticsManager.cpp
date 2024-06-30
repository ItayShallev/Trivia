#include "StatisticsManager.h"
#include "Helper.h"


StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database) {}


vector<HighScoreRow> StatisticsManager::getHighScore() const
{
	return this->m_database->getHighScores();
}


HighScoreRow StatisticsManager::getUserStatistics(const string& username) const
{
	return this->m_database->getUserStatistics(username);
}


/**
 * @brief	Calculates the amount of points a user needs to get based on the answer time, the question timer and the difficulty of the question
 * @note	Based on Kahoot method [https://support.kahoot.com/hc/en-us/articles/115002303908-How-points-work]
 */
uint StatisticsManager::calculatePoints(const double& answerTime, const uint& timePerQuestion, const QuestionDifficulty& difficulty)
{
	return static_cast<uint>(round((1 - ((answerTime / timePerQuestion) / 2)) * Helper::getPointsPossibleForDifficulty(difficulty)));
}
