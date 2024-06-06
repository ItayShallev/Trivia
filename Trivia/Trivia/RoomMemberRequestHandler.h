#pragma once
#include "IRequestHandler.h"
class RequestHandlerFactory;
#include "RequestHandlerFactory.h"
#include "RoomManager.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room& room, std::shared_ptr<LoggedUser> user, RoomManager& roomManager, RequestHandlerFactory* handlerFactory);
	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	Room& m_room;
	std::shared_ptr<LoggedUser> m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult leaveRoom(RequestInfo reqInfo);
	RequestResult getRoomState(RequestInfo reqInfo);
};

