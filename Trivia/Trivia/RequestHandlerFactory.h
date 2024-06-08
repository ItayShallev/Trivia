#pragma once


#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
class MenuRequestHandler;
class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManger;
	IDatabase* m_database;		// TODO: Not in use currently. May be removed later...
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
	GameManager m_gameManager;


public:
	RequestHandlerFactory(IDatabase* database);
	std::shared_ptr<LoginRequestHandler> createLoginRequestHandler();
	std::shared_ptr<MenuRequestHandler> createMenuRequestHandler(std::shared_ptr<LoggedUser> user);
	std::shared_ptr<RoomAdminRequestHandler> createRoomAdminRequestHandler(std::shared_ptr<LoggedUser> user, Room& room);
	std::shared_ptr<RoomMemberRequestHandler> createRoomMemberRequestHandler(std::shared_ptr<LoggedUser> user, Room& room);
	std::shared_ptr<GameRequestHandler> createGameRequestHandler(std::shared_ptr<Game> game, std::shared_ptr<LoggedUser> user);
	GameManager& getGameManager();

	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
};

