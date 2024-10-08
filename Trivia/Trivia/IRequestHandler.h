#pragma once

struct RequestInfo;
struct RequestResult;


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo reqInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo reqInfo) = 0;
};
