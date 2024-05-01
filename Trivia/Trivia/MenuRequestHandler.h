#pragma once
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(RequestInfo reqInfo) override;
	RequestResult handleRequest(RequestInfo reqInfo) override;
};

