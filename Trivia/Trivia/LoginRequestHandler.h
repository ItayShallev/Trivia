#pragma once

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;


class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory* factory);

	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	RequestHandlerFactory* m_handlerFactory;

	RequestResult login(RequestInfo reqInfo);
	RequestResult signup(RequestInfo reqInfo);
	RequestResult continueAuthentication(RequestInfo reqInfo);
};
