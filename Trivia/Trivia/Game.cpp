#include "Game.h"
#include "StatisticsManager.h"


using std::any_of;


Game::Game(const uint& gameId, const map<shared_ptr<LoggedUser>, GameData>& players, const vector<Question>& questions, const RoomData& gameSettings)
{
	this->m_gameId = gameId;
	this->m_players = players;
	this->m_questions = questions;
	this->m_numFinished = 0;
	this->m_gameSettings = gameSettings;

	// Setting the currentQuestion for every player
	for (auto& playerPair : this->m_players)
	{
		GameData& currUserGameData = playerPair.second;
		currUserGameData.currentQuestion = this->m_questions.at(0);
	}
}


Question Game::getQuestionForUser(const shared_ptr<LoggedUser>& user) const
{
	return this->m_players.at(user).currentQuestion;
}


void Game::submitAnswer(const shared_ptr<LoggedUser>& user, const uint& answerId, const double& answerTime)
{
	// Getting the given user's GameData
	GameData& currUserGameData = this->m_players.at(user);

	// Updating the correct/wrong answer count
	if (answerId == currUserGameData.currentQuestion.getCorrectAnswerId())
	{
		currUserGameData.correctAnswerCount++;

		// Adding points according to the answer time and the difficulty of the question
		currUserGameData.points += StatisticsManager::calculatePoints(answerTime, this->m_gameSettings.timePerQuestion, currUserGameData.currentQuestion.getDifficulty());
	}
	else if (answerId == TIME_EXPIRED_ANSWER_ID)
	{
		// Maybe implement some logic related to answers that weren't really answered by the user...
		currUserGameData.wrongAnswerCount++;
	}
	else
	{
		currUserGameData.wrongAnswerCount++;
	}

	// Calculating tha amount of answers the user submitted till now
	uint answersCount = currUserGameData.correctAnswerCount + currUserGameData.wrongAnswerCount;

	// Updating the average answer time
	double totalAnswerTime = ((currUserGameData.averageAnswerTime) * (answersCount - 1)) + answerTime;		// -1 to exclude the new submitted answer
	currUserGameData.averageAnswerTime = totalAnswerTime / (answersCount);

	// Updating the current question for the user (if remained)
	if (answersCount < this->m_questions.size())		// If questions remained
	{
		currUserGameData.currentQuestion = this->m_questions.at(answersCount);
	}
	else												// If no questions remained
	{
		currUserGameData.currentQuestion = Question(L"NO QUESTIONS REMAINED!", vector<AnswerItem>(), 0, QuestionDifficulty::Easy);
		this->m_numFinished++;

		// Changing the user's status
		user->setUserStatus(UserStatus::InResults);
	}
}


void Game::removeUser(const shared_ptr<LoggedUser>& user)
{
	this->m_players.erase(user);
}


bool Game::hasGameEnded() const
{
	return this->m_numFinished == this->m_players.size();
}


uint Game::getGameId() const
{
	return this->m_gameId;
}


map<shared_ptr<LoggedUser>, GameData>& Game::getPlayers()
{
	return this->m_players;
}


void Game::incrementNumFinished()
{
	this->m_numFinished++;
}


bool Game::isAnyPlayerActive() const
{
	return any_of(this->m_players.begin(), this->m_players.end(),
		[](const auto& playerPair) {return playerPair.first->getUserStatus() == UserStatus::InGame;});
}
