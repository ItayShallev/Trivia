#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
class RequestHandlerFactory;
#include "RequestHandlerFactory.h"


class RoomAdminRequestHandler :
    public IRequestHandler
{
public:
	RoomAdminRequestHandler(Room& room,LoggedUser& user,RoomManager& roomManager, RequestHandlerFactory* handlerFactory);
	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;
private:
	Room& m_room;
	LoggedUser& m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult closeRoom(RequestInfo reqInfo);
	RequestResult startGame(RequestInfo reqInfo);
	RequestResult getRoomState(RequestInfo reqInfo);
};

