#include "RoomMemberRequestHandler.h"

#include "Helper.h"
#include "JsonResponsePacketSerializer.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser& user, RoomManager& roomManager, RequestHandlerFactory* handlerFactory) : m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

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
		break;
	case RequestId::GetRoomStateRequestId:
		return getRoomState(reqInfo);
		break;
	default:
		return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()), this);
	}

}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo reqInfo)
{
	// remove the user from the room
	this->m_room.removeUser(&this->m_user);

	// create a new menu request handler
	IRequestHandler* newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);

	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse()), newHandler);
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo reqInfo)
{
	// get the room state
	RoomState currRoomState = this->m_roomManager.getRoomState(this->m_room);

	// create the room state response
	GetRoomStateResponse roomStateResp = Helper::buildRoomStateResponse(currRoomState);

	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(roomStateResp), this);
}
