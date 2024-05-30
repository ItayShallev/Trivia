#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RequestResult LoginRequestHandler::login(RequestInfo reqInfo)
{
	// create an empty result
	RequestResult reqResult;

	// get the manager
	LoginManager manager = m_handlerFactory.getLoginManager();

	// create a login request
	LoginRequest loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);

	// sign the user
	bool success = manager.login(loginReq.username, loginReq.password);

	// if signing failed
	if (!success)
	{
		// create error response
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse());
		reqResult.newHandler = m_handlerFactory.createLoginRequestHandler();
		return reqResult;
	}

	// create the login response
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(LoginResponse());
	reqResult.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(loginReq.username));

	// return the response
	return reqResult;
}

RequestResult LoginRequestHandler::signup(RequestInfo reqInfo)
{
	// create an empty result
	RequestResult reqResult;

	// get the manager
	LoginManager manager = m_handlerFactory.getLoginManager();

	// create a signup request
	SignupRequest signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);

	// sign the user
	bool success = manager.signup(signupReq.username, signupReq.password, signupReq.mail);

	// if signing failed
	if (!success)
	{
		// create error response
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse());
		reqResult.newHandler = m_handlerFactory.createLoginRequestHandler();
		return reqResult;
	}

	// create the signup response
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(SignupResponse());
	reqResult.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(signupReq.username));

	// return the response
	return reqResult;
}

RequestResult LoginRequestHandler::continueAuthentication(RequestInfo reqInfo)
{
	// create an empty result
	RequestResult reqResult;

	// get the manager
	LoginManager manager = m_handlerFactory.getLoginManager();

	// create the request
	CheckIfUserExistsRequest checkIfUsersExistsReq = JsonRequestPacketDeserializer::deserializeCheckIfUserExistsRequest(reqInfo.buffer);

	// check if the user exists
	bool doesUserExist = manager.doesUserExist(checkIfUsersExistsReq.username);

	// create the response
	CheckIfUserExistsResponse response(doesUserExist);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	reqResult.newHandler = m_handlerFactory.createLoginRequestHandler();

	// return the response
	return reqResult;
}

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory* factory) : m_handlerFactory(*factory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    return reqInfo.id == RequestId::LoginRequestId || reqInfo.id == RequestId::SignupRequestId || reqInfo.id == RequestId::CheckIfUserExistsRequestId;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
	// create an empty result
	switch (reqInfo.id)
	{
	case RequestId::LoginRequestId:
		// login the user
		return login(reqInfo);
		break;

	case RequestId::SignupRequestId:
		return signup(reqInfo);
		break;

	case RequestId::CheckIfUserExistsRequestId:
		return continueAuthentication(reqInfo);
		break;

	default:

		// create error response
		RequestResult retResult;
		retResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse());
		retResult.newHandler = m_handlerFactory.createLoginRequestHandler();
		return retResult;
	}

}