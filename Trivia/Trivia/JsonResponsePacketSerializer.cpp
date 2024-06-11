#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include "Helper.h"


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
	return buildResponse(ResponseId::GetPersonalStatisticsResponseId, getPersonalStatsResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const CheckIfUserExistsResponse& checkIfUserExistsResponse)
{
	return buildResponse(ResponseId::CheckIfUserExistsResponseId, checkIfUserExistsResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& closeRoomResponse)
{
	return buildResponse(ResponseId::CloseRoomResponseId, closeRoomResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& startGameResponse)
{
	return buildResponse(ResponseId::StartGameResponseId, startGameResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& getRoomStateResponse)
{
	return buildResponse(ResponseId::GetRoomStateResponseId, getRoomStateResponse);
}


Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& leaveRoomResponse)
{
	return buildResponse(ResponseId::LeaveRoomResponseId, leaveRoomResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetGameResultResponse& getGameResultResponse)
{
	return buildResponse(ResponseId::GetGameResultResponseId, getGameResultResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SubmitAnswerResponse& submitAnswerResponse)
{
	return buildResponse(ResponseId::SubmitAnswerResponseId, submitAnswerResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetQuestionResponse& getQuestionResponse)
{
	return buildResponse(ResponseId::GetQuestionResponseId, getQuestionResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveGameResponse& leaveGameResponse)
{
	return buildResponse(ResponseId::LeaveGameResponseId, leaveGameResponse);
}
