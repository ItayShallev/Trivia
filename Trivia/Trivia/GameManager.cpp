#include "GameManager.h"


GameManager::GameManager(IDatabase* database) : m_database(database) { }


std::shared_ptr<Game> GameManager::createGame(const Room& room)
{
	// Initializing a players map containing the users from the given room
	map<std::shared_ptr<LoggedUser>, GameData> players;
	for (auto& loggedUser : room.getUsers())
	{
		players[loggedUser] = GameData();
	}

	// Creating a new game dynamically (the game has the same ID as the room)
	std::shared_ptr<Game> newGame = std::make_shared<Game>(room.getId(), players, this->m_database->getRandomQuestions(room.getNumOfQuestions()));

	// pushing the game to the m_games vector
	m_games.push_back(newGame);

	return newGame;
}


void GameManager::deleteRoom(const uint& gameId)
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


std::shared_ptr<Game> GameManager::getGameById(const uint& gameId) const
{
	auto matchGameIdLambda = [gameId](const std::shared_ptr<Game>& game) { return game->getGameId() == gameId; };

	auto it = std::find_if(m_games.begin(), m_games.end(), matchGameIdLambda);

	return (it != m_games.end()) ? *it : nullptr;
}
