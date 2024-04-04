#include "LoginRequestHandler.h"
#include "Tools.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    return reqInfo.id == RequestId::LoginRequest;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
    RequestResult newResult;
    return newResult;
}
