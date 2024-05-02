#pragma once
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo reqInfo) override;
	RequestResult handleRequest(RequestInfo reqInfo) override;
};

