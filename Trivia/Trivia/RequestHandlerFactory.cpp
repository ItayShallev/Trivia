#include "RequestHandlerFactory.h"


using std::make_shared;


RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
	: m_database(database), m_loginManger(database, vector<shared_ptr<LoggedUser>>()), m_StatisticsManager(database), m_gameManager(GameManager(database)) { }


shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return make_shared<LoginRequestHandler>(this);
}


shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(shared_ptr<LoggedUser> user)
{
	return make_shared<MenuRequestHandler>(user, this);
}


shared_ptr<RoomAdminRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(shared_ptr<LoggedUser> user, Room& room)
{
	return make_shared<RoomAdminRequestHandler>(room, user, this->m_roomManager, this);
}


shared_ptr<RoomMemberRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(shared_ptr<LoggedUser> user, Room& room)
{
	return make_shared<RoomMemberRequestHandler>(room, user, this->m_roomManager, this);
}


shared_ptr<GameRequestHandler> RequestHandlerFactory::createGameRequestHandler(shared_ptr<Game> game, shared_ptr<LoggedUser> user)
{
	return make_shared<GameRequestHandler>(game, user, this->m_gameManager, this);
}


GameManager& RequestHandlerFactory::getGameManager()
{
	return this->m_gameManager;
}


LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManger;
}


RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}


StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}
