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
