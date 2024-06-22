#pragma once

#include <vector>
#include <map>
#include <memory>
#include "GameStructures.h"
#include "Question.h"
#include "LoggedUser.h"


using std::map;
using std::shared_ptr;


class Game
{
public:
	Game(const uint& gameId, const map<shared_ptr<LoggedUser>, GameData>& players, const vector<Question>& questions, const RoomData& gameSettings);

	Question getQuestionForUser(const shared_ptr<LoggedUser>& user) const;
	void submitAnswer(const shared_ptr<LoggedUser>& user, const uint& answerId, const double& answerTime);
	void removeUser(const shared_ptr<LoggedUser>& user);
	bool hasGameEnded() const;

	uint getGameId() const;
	map<shared_ptr<LoggedUser>, GameData>& getPlayers();

	void incrementNumFinished();
	bool isAnyPlayerActive() const;

private:
	uint m_gameId;
	map<shared_ptr<LoggedUser>, GameData> m_players;
	vector<Question> m_questions;
	uint m_numFinished;
	RoomData m_gameSettings;
};
