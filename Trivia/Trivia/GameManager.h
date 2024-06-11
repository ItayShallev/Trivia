#pragma once

#include <vector>
#include "Game.h"
#include "Room.h"
#include "IDatabase.h"


class GameManager
{
public:
	GameManager(IDatabase* database);
	std::shared_ptr<Game> createGame(const Room& room);
	void deleteRoom(const uint& gameId);

	std::shared_ptr<Game> getGameById(const uint& gameId) const;

private:
	IDatabase* m_database;
	vector<std::shared_ptr<Game>> m_games;
};
