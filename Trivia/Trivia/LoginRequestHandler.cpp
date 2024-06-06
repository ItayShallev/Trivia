#include "LoginRequestHandler.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

RequestResult LoginRequestHandler::login(RequestInfo reqInfo)
{
	// get the manager
	LoginManager manager = m_handlerFactory.getLoginManager();
	
	// create a login request
	LoginRequest loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);

	// sign the user
	bool success = manager.login(loginReq.username, loginReq.password);

	// if signing failed
	if (!success)
	{
		Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
			std::shared_ptr<LoginRequestHandler>(this, [](LoginRequestHandler*) {}));
	}

	// IMPORTANT: creating a new shared pointer to a LoggedUser object, unique for the current user
	// (This LoggedUser will be referenced throughout the program and will be one and only)
	std::shared_ptr<LoggedUser> thisUser = std::make_shared<LoggedUser>(loginReq.username);

	// return the login response
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(LoginResponse()),
		this->m_handlerFactory.createMenuRequestHandler(thisUser));
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
		Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
			std::shared_ptr<LoginRequestHandler>(this, [](LoginRequestHandler*) {}));
	}

	// IMPORTANT: creating a new shared pointer to a LoggedUser object, unique for the current user
	// (This LoggedUser will be referenced throughout the program and will be one and only)
	std::shared_ptr<LoggedUser> thisUser = std::make_shared<LoggedUser>(signupReq.username);

	// return the signup response
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(LoginResponse()),
		this->m_handlerFactory.createMenuRequestHandler(thisUser));
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

	// return the authentication response
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(response), 
	std::shared_ptr<LoginRequestHandler>(this, [](LoginRequestHandler*){}));
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
		return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
			std::shared_ptr<LoginRequestHandler>(this, [](LoginRequestHandler*) {}));
	}
}