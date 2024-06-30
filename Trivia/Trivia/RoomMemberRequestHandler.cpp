#include "RoomMemberRequestHandler.h"
#include "Helper.h"
#include "JsonResponsePacketSerializer.h"


RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, shared_ptr<LoggedUser> user, RoomManager& roomManager, RequestHandlerFactory* handlerFactory)
	: m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory) { }


bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	RequestId reqId = reqInfo.id;
	return
		reqId == RequestId::LeaveRoomRequestId ||
		reqId == RequestId::GetRoomStateRequestId;
}


RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo reqInfo)
{
	switch (reqInfo.id)
	{
	case RequestId::LeaveRoomRequestId:
		return leaveRoom(reqInfo);

	case RequestId::GetRoomStateRequestId:
		return getRoomState(reqInfo);

	default:
		return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
			shared_ptr<RoomMemberRequestHandler>(this, [](RoomMemberRequestHandler*) {}));
	}
}


RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo reqInfo)
{
	// remove the user from the room
	this->m_room.removeUser(this->m_user);

	// change the user status to menu
	this->m_user->setUserStatus(UserStatus::InMenu);

	// Checking if the current user was the last to leave the room
	if (this->m_room.getUsers().empty())
	{
		// change the user status to in game
		this->m_user->setUserStatus(UserStatus::InMenu);

		// Deleting the room from memory
		this->m_roomManager.deleteRoom(this->m_room.getId());
	}
	 
	// create a new menu request handler
	shared_ptr<MenuRequestHandler> newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);

	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse()), newHandler);
}


RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo reqInfo)
{
	// get the room state
	RoomState currRoomState = this->m_roomManager.getRoomState(this->m_room);

	// create the room state response
	GetRoomStateResponse roomStateResp = Helper::buildRoomStateResponse(currRoomState);

	// if the room has started playing
	if(currRoomState.roomStatus == RoomStatus::Playing)
	{
		// change the user status to in game
		this->m_user->setUserStatus(UserStatus::InGame);

		// get the game object
		shared_ptr<Game> game = this->m_handlerFactory->getGameManager().getGameById(this->m_room.getId());

		// create the new game handler
		shared_ptr<GameRequestHandler> gameHandler = this->m_handlerFactory->createGameRequestHandler(game, this->m_user);

		// build and return the request result
		return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(roomStateResp), gameHandler);

	}

	// build and return the request result
	return (Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(roomStateResp),
		shared_ptr<RoomMemberRequestHandler>(this, [](RoomMemberRequestHandler*) {})));
}
