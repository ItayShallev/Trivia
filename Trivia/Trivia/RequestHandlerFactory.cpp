#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_database(database), m_loginManger(database, *(new vector<LoggedUser>)), m_StatisticsManager(database)
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& user)
{
	return new MenuRequestHandler(user, this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room& room)
{
	return new RoomAdminRequestHandler(room, user, this->m_roomManager, this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user, Room& room)
{
	return new RoomMemberRequestHandler(room, user, this->m_roomManager, this);
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
