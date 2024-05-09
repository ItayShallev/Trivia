#pragma once

#include <map>
#include "Structures.h"

using std::to_string;
using std::map;


class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	static Buffer serializeResponse(const LoginResponse& loginResponse);
	static Buffer serializeResponse(const SignupResponse& signupResponse);

	static Buffer serializeResponse(const LogoutResponse& signupResponse);
	static Buffer serializeResponse(const GetRoomResponse& signupResponse);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& signupResponse);
	static Buffer serializeResponse(const JoinRoomResponse& signupResponse);
	static Buffer serializeResponse(const CreateRoomResponse& signupResponse);
	static Buffer serializeResponse(const GetHighScoreResponse& signupResponse);
	static Buffer serializeResponse(const GetPersonalStatsResponse& signupResponse);
};
