#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
	: m_database(database), m_loginManger(database, vector<LoggedUser>()), m_StatisticsManager(database), m_gameManager(GameManager(database)) { }

std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::make_shared<LoginRequestHandler>(this);
}

std::shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(std::shared_ptr<LoggedUser> user)
{
	return std::make_shared<MenuRequestHandler>(user, this);
}

std::shared_ptr<RoomAdminRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(std::shared_ptr<LoggedUser> user, Room& room)
{
	return std::make_shared<RoomAdminRequestHandler>(room, user, this->m_roomManager, this);
}

std::shared_ptr<RoomMemberRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(std::shared_ptr<LoggedUser> user, Room& room)
{
	return std::make_shared<RoomMemberRequestHandler>(room, user, this->m_roomManager, this);
}

std::shared_ptr<GameRequestHandler> RequestHandlerFactory::createGameRequestHandler(std::shared_ptr<Game> game, std::shared_ptr<LoggedUser> user)
{
	return std::make_shared<GameRequestHandler>(game, user, this->m_gameManager, this);
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return this->m_gameManager;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	// return the login manager
	return this->m_loginManger;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	// return the room manager
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	// return the statistics manager
	return this->m_StatisticsManager;
}
