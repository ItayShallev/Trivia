#pragma once

#include <vector>
#include <map>
#include <memory>
#include "Structures.h"
#include "Question.h"
#include "LoggedUser.h"


class Game
{
public:
	Game(const uint& gameId, const map<std::shared_ptr<LoggedUser>, GameData>& players, const vector<Question>& questions);

	Question getQuestionForUser(const std::shared_ptr<LoggedUser>& user);
	void submitAnswer(const std::shared_ptr<LoggedUser>& user, const uint& answerId, const double& answerTime);
	void removeUser(const std::shared_ptr<LoggedUser>& user);
	bool isGameEnded() const;

	uint getGameId() const;
	map<std::shared_ptr<LoggedUser>, GameData> getPlayers() const;


private:
	uint m_gameId;
	map<std::shared_ptr<LoggedUser>, GameData> m_players;
	vector<Question> m_questions;
	uint m_numFinished;
};
