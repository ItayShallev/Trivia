#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;


class LoginRequestHandler : public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(RequestInfo reqInfo);
	RequestResult signup(RequestInfo reqInfo);
public:
	LoginRequestHandler(RequestHandlerFactory* factory);
	bool isRequestRelevant(RequestInfo reqInfo) override;
	RequestResult handleRequest(RequestInfo reqInfo) override;
};
