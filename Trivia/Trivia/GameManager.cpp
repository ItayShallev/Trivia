#include "GameManager.h"


using std::make_shared;
using std::find_if;


GameManager::GameManager(IDatabase* database) : m_database(database) { }


shared_ptr<Game> GameManager::createGame(const Room& room)
{
	// Initializing a players map containing the users from the given room
	map<shared_ptr<LoggedUser>, GameData> players;
	for (auto& loggedUser : room.getUsers())
	{
		players[loggedUser] = GameData();
	}

	// Creating a new game dynamically (the game has the same ID as the room)
	shared_ptr<Game> newGame = make_shared<Game>(room.getId(), players, this->m_database->getRandomQuestions(room.getNumOfQuestions()), room.getRoomData());

	// pushing the game to the m_games vector
	m_games.push_back(newGame);

	return newGame;
}


void GameManager::deleteGame(const uint& gameId)
{
	// Iterating over the games vector searching for a game with the given game ID
	for (auto it = this->m_games.begin(); it != this->m_games.end(); )
	{
		if ((*it)->getGameId() == gameId)
		{
			it = this->m_games.erase(it);		// Deleting the game from the vector (and from the memory...)
		}
		else
		{
			++it;		// Advancing to the next game in the vector
		}
	}
}


shared_ptr<Game> GameManager::getGameById(const uint& gameId) const
{
	auto matchGameIdLambda = [gameId](const shared_ptr<Game>& game) { return game->getGameId() == gameId; };

	auto it = find_if(m_games.begin(), m_games.end(), matchGameIdLambda);

	return (it != m_games.end()) ? *it : nullptr;
}


IDatabase* GameManager::getDatabase() const
{
	return this->m_database;
}
