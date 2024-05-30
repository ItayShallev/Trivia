#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include "Helper.h"
#include "Structures.h"


using std::to_string;
using json = nlohmann::json;


Buffer JsonResponsePacketSerializer::buildResponse(const ResponseId& responseId, json j)
{
	string jsonString = j.dump();
	string response = Helper::padNumWith0(responseId, ID_BYTE_LENGTH) + Helper::padNumWith0(jsonString.length()) + jsonString;

	return Helper::turnStringIntoBuffer(response);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
	return buildResponse(ResponseId::ErrorResponseId, errorResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	return buildResponse(ResponseId::LoginResponseId, loginResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	return buildResponse(ResponseId::SignupResponseId, signupResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& logoutResponse)
{
	return buildResponse(ResponseId::LogoutResponseId, logoutResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& getRoomsResponse)
{
	return buildResponse(ResponseId::GetRoomsResponseId, getRoomsResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse)
{
	return buildResponse(ResponseId::GetPlayersInRoomResponseId, getPlayersInRoomResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& joinRoomResponse)
{
	return buildResponse(ResponseId::JoinRoomResponseId, joinRoomResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& createRoomResponse)
{
	return buildResponse(ResponseId::CreateRoomResponseId, createRoomResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& getHighScoreResponse)
{
	return buildResponse(ResponseId::GetHighScoreResponseId, getHighScoreResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& getPersonalStatsResponse)
{
	return buildResponse(ResponseId::GetPersonalStatsResponseId, getPersonalStatsResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const CheckIfUserExistsResponse& checkIfUserExistsResponse)
{
	return buildResponse(ResponseId::CheckIfUserExistsResponseId, checkIfUserExistsResponse);
}
