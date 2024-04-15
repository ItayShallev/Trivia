#pragma once

#include "IRequestHandler.h"


class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo reqInfo) override;
	RequestResult handleRequest(RequestInfo reqInfo) override;
};
