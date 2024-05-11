#pragma once


#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
class MenuRequestHandler;
class LoginRequestHandler;
#include "MenuRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManger;
	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;


public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& user);
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
};

