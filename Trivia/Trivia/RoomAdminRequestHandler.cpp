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
        break;
    case RequestId::StartGameRequestId:
        return startGame(reqInfo);
        break;
    case RequestId::GetRoomStateRequestId:
        return getRoomState(reqInfo);
        break;
    default:
        return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
            std::shared_ptr<RoomAdminRequestHandler>(this, [](RoomAdminRequestHandler*) {}));
    }

}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo reqInfo)
{
    // TODO: check if that's all you need to do
    // change the room status to closed
    this->m_room.setRoomStatus(RoomStatus::Closed);

    // TODO: check if room state changed
    // get the room state
    RoomState currRoomState = this->m_roomManager.getRoomState(this->m_room);

    // return a room state response with the new room status
    // create the room state response
    GetRoomStateResponse roomStateResp = Helper::buildRoomStateResponse(currRoomState);

    // create the new handler
    std::shared_ptr<MenuRequestHandler> newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);

    // build and return the request result
    return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(roomStateResp), newHandler);
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo reqInfo)
{
    // TODO: check if that's all you need to do
    // change the room status to playing
    this->m_room.setRoomStatus(RoomStatus::Playing);

    // TODO: check if room state changed
    // get the room state
    RoomState currRoomState = this->m_roomManager.getRoomState(this->m_room);

    // return a room state response with the new room status
    // create the room state response
    GetRoomStateResponse roomStateResp = Helper::buildRoomStateResponse(currRoomState);

    // build and return the request result
    return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(roomStateResp),
        std::shared_ptr<RoomAdminRequestHandler>(this, [](RoomAdminRequestHandler*) {}));
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
