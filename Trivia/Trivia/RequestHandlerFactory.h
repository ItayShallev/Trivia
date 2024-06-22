#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

class MenuRequestHandler;
class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;


using std::shared_ptr;


class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);

	shared_ptr<LoginRequestHandler> createLoginRequestHandler();
	shared_ptr<MenuRequestHandler> createMenuRequestHandler(shared_ptr<LoggedUser> user);
	shared_ptr<RoomAdminRequestHandler> createRoomAdminRequestHandler(shared_ptr<LoggedUser> user, Room& room);
	shared_ptr<RoomMemberRequestHandler> createRoomMemberRequestHandler(shared_ptr<LoggedUser> user, Room& room);
	shared_ptr<GameRequestHandler> createGameRequestHandler(shared_ptr<Game> game, shared_ptr<LoggedUser> user);

	GameManager& getGameManager();
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();

private:
	LoginManager m_loginManger;
	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
	GameManager m_gameManager;
};
