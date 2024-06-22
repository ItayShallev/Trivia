#pragma once

#include <vector>
#include "Game.h"
#include "Room.h"
#include "IDatabase.h"


using std::shared_ptr;


class GameManager
{
public:
	GameManager(IDatabase* database);
	shared_ptr<Game> createGame(const Room& room);
	void deleteGame(const uint& gameId);

	shared_ptr<Game> getGameById(const uint& gameId) const;
	IDatabase* getDatabase() const;

private:
	IDatabase* m_database;
	vector<shared_ptr<Game>> m_games;
};
