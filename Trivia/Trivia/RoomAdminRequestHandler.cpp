#include "RoomAdminRequestHandler.h"
#include "Helper.h"
#include "JsonResponsePacketSerializer.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, std::shared_ptr<LoggedUser> user, RoomManager& roomManager, RequestHandlerFactory* handlerFactory)
	: m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory) { }

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    RequestId reqId = reqInfo.id;
    return
        reqId == RequestId::CloseRoomRequestId ||
        reqId == RequestId::StartGameRequestId ||
        reqId == RequestId::GetRoomStateRequestId;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo reqInfo)
{
    switch (reqInfo.id)
    {
    case RequestId::CloseRoomRequestId:
        return closeRoom(reqInfo);

    case RequestId::StartGameRequestId:
        return startGame(reqInfo);

    case RequestId::GetRoomStateRequestId:
        return getRoomState(reqInfo);

    default:
        return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
            std::shared_ptr<RoomAdminRequestHandler>(this, [](RoomAdminRequestHandler*) {}));
    }

}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo reqInfo)
{
    this->m_room.removeUser(this->m_user);

    // Checking if the admin was the only one in the room
    if (this->m_room.getUsers().empty())
    {
	    // Deleting the room from memory
		this->m_roomManager.deleteRoom(this->m_room.getId());
    }
    else
    {
		// Changing the room status to closed to notify the participants that the room was closed, and they need to leave it
        this->m_room.setRoomStatus(RoomStatus::Closed);
    }

	// change the room status to closed
    this->m_room.setRoomStatus(RoomStatus::Closed);

    // create the new handler
    std::shared_ptr<MenuRequestHandler> newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);

    // build and return the request result
    return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse()), newHandler);
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo reqInfo)
{
    // change the room status to playing
    this->m_room.setRoomStatus(RoomStatus::Playing);

    // get the room state
    RoomState currRoomState = this->m_roomManager.getRoomState(this->m_room);

    // create the game
	std::shared_ptr<Game> game = this->m_handlerFactory->getGameManager().createGame(this->m_room);

    // create a new game handler
    std::shared_ptr<GameRequestHandler> newGameHandler = this->m_handlerFactory->createGameRequestHandler(game, this->m_user);

    // build and return the request result
    return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(StartGameResponse()), newGameHandler);
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo reqInfo)
{
    // get the room state
    RoomState currRoomState = this->m_roomManager.getRoomState(this->m_room);

    // create the room state response
    GetRoomStateResponse roomStateResp = Helper::buildRoomStateResponse(currRoomState);

    // build and return the request result
    return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(roomStateResp),
        std::shared_ptr<RoomAdminRequestHandler>(this, [](RoomAdminRequestHandler*) {}));
}
