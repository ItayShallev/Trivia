#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    return reqInfo.id == RequestId::LoginRequestId || reqInfo.id == RequestId::SignupRequestId;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
	// currently useless
	IRequestHandler* newHandler = nullptr;

	// init an empty buffer
	Buffer response;

	switch (reqInfo.id)
	{
	case RequestId::LoginRequestId:
	{
		// set the new handler to a new login handler
		newHandler = new LoginRequestHandler();

		// get the login request
		LoginResponse logResp;
		response = JsonResponsePacketSerializer::serializeResponse(logResp);
		break;
	}

	case RequestId::SignupRequestId:
	{
		// set the new handler to a new login handler
		newHandler = new LoginRequestHandler();

		// get the login request
		SignupResponse signupResp;
		response = JsonResponsePacketSerializer::serializeResponse(signupResp);
		break;
	}
	}

	// build and return a request result
    RequestResult newResult;
	newResult.response = response;
	newResult.newHandler = newHandler;
    return newResult;
}
