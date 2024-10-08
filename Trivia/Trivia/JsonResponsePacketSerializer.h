#pragma once

#include <map>
#include "json.hpp"
#include "GameStructures.h"
#include "ResponseStructures.h"

using json = nlohmann::json;
using std::to_string;
using std::map;


class JsonResponsePacketSerializer
{
public:
	static Buffer buildResponse(const ResponseId& responseId, json j);

	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	static Buffer serializeResponse(const LoginResponse& loginResponse);
	static Buffer serializeResponse(const SignupResponse& signupResponse);
	static Buffer serializeResponse(const LogoutResponse& logoutResponse);
	static Buffer serializeResponse(const GetRoomsResponse& getRoomsResponse);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	static Buffer serializeResponse(const JoinRoomResponse& joinRoomResponse);
	static Buffer serializeResponse(const CreateRoomResponse& createRoomResponse);
	static Buffer serializeResponse(const GetHighScoreResponse& getHighScoreResponse);
	static Buffer serializeResponse(const GetPersonalStatsResponse& getPersonalStatsResponse);
	static Buffer serializeResponse(const CheckIfUserExistsResponse& checkIfUserExistsResponse);
	static Buffer serializeResponse(const CloseRoomResponse& closeRoomResponse);
	static Buffer serializeResponse(const StartGameResponse& startGameResponse);
	static Buffer serializeResponse(const GetRoomStateResponse& getRoomStateResponse);
	static Buffer serializeResponse(const LeaveRoomResponse& leaveRoomResponse);
	static Buffer serializeResponse(const GetGameResultResponse& getGameResultResponse);
	static Buffer serializeResponse(const SubmitAnswerResponse& submitAnswerResponse);
	static Buffer serializeResponse(const GetQuestionResponse& getQuestionResponse);
	static Buffer serializeResponse(const LeaveGameResponse& leaveGameResponse);
};
