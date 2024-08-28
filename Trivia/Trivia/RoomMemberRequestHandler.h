#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"

class RequestHandlerFactory;


using std::shared_ptr;


class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room& room, shared_ptr<LoggedUser> user, RoomManager& roomManager, RequestHandlerFactory* handlerFactory);

	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	Room& m_room;
	shared_ptr<LoggedUser> m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult leaveRoom(RequestInfo reqInfo);
	RequestResult getRoomState(RequestInfo reqInfo);
};
