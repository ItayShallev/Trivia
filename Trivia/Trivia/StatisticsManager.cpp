#include "StatisticsManager.h"
#include "Helper.h"


/**
 * @brief	Constructor, Initializes a new StatisticsManager instance
 * @param	database		The database to set to the new StatisticsManager object
 */
StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database) {}


/**
 * @brief	Returns a leaderboard containing the 5 best users
 * @return	A vector containing the usernames of the 5 best users
 */
vector<string> StatisticsManager::getHighScore() const
{
	return this->m_database->getHighScores();
}


/**
 * @brief	Returns the statistics of the user with the given username
 * @param	username		The username of the user to get its statistics
 * @return	A vector containing the user all-time statistics
 */
vector<string> StatisticsManager::getUserStatistics(const string& username) const
{
	return this->m_database->getUserStatistics(username);
}


int StatisticsManager::calculateRoundPoints(const double& answerTime, const uint& timePerQuestion, const QuestionDifficulty& difficulty)
{
	return static_cast<int>(round((1 - ((answerTime / timePerQuestion) / 2)) * Helper::getPointsPossibleForDifficulty(difficulty)));
}
