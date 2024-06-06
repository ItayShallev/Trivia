#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
class RequestHandlerFactory;
#include "RequestHandlerFactory.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(std::shared_ptr<LoggedUser> user, RequestHandlerFactory* factory);
	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	std::shared_ptr<LoggedUser> m_user;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(RequestInfo reqInfo);
	RequestResult getRooms(RequestInfo reqInfo);
	RequestResult getPlayersInRoom(RequestInfo reqInfo);
	RequestResult getPersonalStats(RequestInfo reqInfo);
	RequestResult getHighScore(RequestInfo reqInfo);
	RequestResult joinRoom(RequestInfo reqInfo);
	RequestResult createRoom(RequestInfo reqInfo);
};

