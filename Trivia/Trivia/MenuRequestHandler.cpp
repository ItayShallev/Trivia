#include "MenuRequestHandler.h"
#include "Communicator.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"


MenuRequestHandler::MenuRequestHandler(shared_ptr<LoggedUser> user, RequestHandlerFactory* factory)
	: m_user(user), m_handlerFactory(factory) { }


bool MenuRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	uint reqId = reqInfo.id;
	return
		reqId == RequestId::CreateRoomRequestId ||
		reqId == RequestId::GetRoomsRequestId ||
		reqId == RequestId::GetPlayersInRoomRequestId ||
		reqId == RequestId::JoinRoomRequestId ||
		reqId == RequestId::GetPersonalStatisticsRequestId ||
		reqId == RequestId::GetHighScoreRequestId ||
		reqId == RequestId::LogoutRequestId;
}


RequestResult MenuRequestHandler::handleRequest(RequestInfo reqInfo)
{
	switch (reqInfo.id)
	{
	case RequestId::CreateRoomRequestId:
		return createRoom(reqInfo);

	case RequestId::GetRoomsRequestId:
		return getRooms(reqInfo);

	case RequestId::GetPlayersInRoomRequestId:
		return getPlayersInRoom(reqInfo);

	case RequestId::JoinRoomRequestId:
		return joinRoom(reqInfo);

	case RequestId::GetPersonalStatisticsRequestId:
		return getPersonalStats(reqInfo);

	case RequestId::GetHighScoreRequestId:
		return getHighScore(reqInfo);

	case RequestId::LogoutRequestId:
		return signout(reqInfo);

	default:
		return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
			shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {}));
	}
}


RequestResult MenuRequestHandler::signout(RequestInfo reqInfo)
{
	// logout the user
	bool success = m_handlerFactory->getLoginManager().logout(this->m_user->getUserName());

	if (!success)
	{
		// Building an error response, passing a shared pointer with a custom empty deleter that will ensure that 'this' will not be tried to be deleted
		return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
			shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {}));
	}

	// build and return the result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(LogoutResponse()), m_handlerFactory->createLoginRequestHandler());
}


RequestResult MenuRequestHandler::getRooms(RequestInfo reqInfo)
{
	// get the rooms
	vector<RoomData> rooms = this->m_handlerFactory->getRoomManager().getRooms();

	// build the room response
	GetRoomsResponse roomResp = GetRoomsResponse{
		1,
		rooms };


	// build and return the result
	return (Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(roomResp),
		shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {})));
}


RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo reqInfo)
{
	// get the players-in-room request
	GetPlayersInRoomRequest playersInRoomReq = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(reqInfo.buffer);

	// get the rooms data
	vector<RoomData> roomsData = this->m_handlerFactory->getRoomManager().getRooms();

	// init an empty players vector
	vector<string> players;

	// iterate through the room data
	for (const RoomData& currRoomData : roomsData)
	{
		// if we found the room we're looking for
		if (currRoomData.id == playersInRoomReq.roomID)
		{
			// get the room
			Room currRoom = this->m_handlerFactory->getRoomManager().getRoom(currRoomData.id);

			// get all the room's users
			players = currRoom.getAllUsers();

			// break from the loop
			break;
		}
	}

	// build the players-in-room response
	GetPlayersInRoomResponse playersInRoomResp = GetPlayersInRoomResponse{ players };

	// build and return the result
	return (Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(playersInRoomResp),
		shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {})));
}


RequestResult MenuRequestHandler::getPersonalStats(RequestInfo reqInfo)
{
	// get the user statistics
	HighScoreRow userStats = this->m_handlerFactory->getStatisticsManager().getUserStatistics(this->m_user->getUserName());

	//  build the response
	GetPersonalStatsResponse personalStatsResp = GetPersonalStatsResponse{ 1, userStats };

	// build and return the result
	return (Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(personalStatsResp),
		shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {})));
}


RequestResult MenuRequestHandler::getHighScore(RequestInfo reqInfo)
{
	// get the high score
	vector<HighScoreRow> highScore = this->m_handlerFactory->getStatisticsManager().getHighScore();

	// build the response
	GetHighScoreResponse highScoreResp = GetHighScoreResponse{ 1, highScore };

	// build and return the result
	return (Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(highScoreResp),
		shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {})));
}


RequestResult MenuRequestHandler::joinRoom(RequestInfo reqInfo)
{
	// get the rooms
	JoinRoomRequest joinRoomReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer);

	// get the rooms data
	vector<RoomData> roomsData = this->m_handlerFactory->getRoomManager().getRooms();

	Room* wantedRoom = nullptr;

	// iterate through the room data
	for (const RoomData& currRoomData : roomsData)
	{
		// if we found the room we're looking for
		if (currRoomData.id == joinRoomReq.roomID)
		{
			// get the room
			Room& currRoom = this->m_handlerFactory->getRoomManager().getRoom(currRoomData.id);

			// Tyring to join the room
			if (!currRoom.addUser(this->m_user))		// If the room joining has failed - send error response
			{
				return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
					shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {}));
			}

			// set the wanted room
			wantedRoom = &currRoom;

			// break from the loop
			break;
		}
	}

	// something went wrong
	if (wantedRoom == nullptr)
	{
		Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()), 
			shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {}));
	}

	// Changing the user status
	this->m_user->setUserStatus(UserStatus::InWaitingRoom);

	//  build and return the result
	return (Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse()),
		this->m_handlerFactory->createRoomMemberRequestHandler(this->m_user, *wantedRoom)));
}


RequestResult MenuRequestHandler::createRoom(RequestInfo reqInfo)
{
	// create a new create-room request
	CreateRoomRequest newRoomReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(reqInfo.buffer);

	// returning an ErrorResponse if the player chose an invalid max-players value
	if (newRoomReq.maxPlayers <= 0 || newRoomReq.maxPlayers > LIMIT_OF_MAX_PLAYERS_IN_ROOM)
	{
		Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
			shared_ptr<MenuRequestHandler>(this, [](MenuRequestHandler*) {}));
	}

	// build the room metadata
	uint roomId = RoomManager::generateRoomID();

	RoomData newRoomData = {
		roomId,
		newRoomReq.roomName,
		newRoomReq.admin,
		newRoomReq.maxPlayers,
		newRoomReq.questionCount,
		newRoomReq.answerTimeout,
		RoomStatus::Waiting
	};

	// Creating the room
	this->m_handlerFactory->getRoomManager().createRoom(this->m_user, newRoomData);

	// get the created room
	Room& room = this->m_handlerFactory->getRoomManager().getRoom(roomId);

	// Changing the user status
	this->m_user->setUserStatus(UserStatus::InWaitingRoom);

	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse{ 1, newRoomData }),
		this->m_handlerFactory->createRoomAdminRequestHandler(this->m_user, room));
}
