#pragma once

#include <string>
#include <vector>
#include "json.hpp"
#include "GameStructures.h"


using std::string;
using std::vector;
using nlohmann::json;


typedef unsigned int uint;


struct ErrorResponse
{
	string message = "ERROR";
};
void to_json(json& j, const ErrorResponse& response);


struct LoginResponse
{
	uint status = 1;
};
void to_json(json& j, const LoginResponse& response);


struct SignupResponse
{
	uint status = 1;
};
void to_json(json& j, const SignupResponse& response);


struct LogoutResponse
{
	uint status = 1;
};
void to_json(json& j, const LogoutResponse& response);


struct GetRoomsResponse
{
	uint status = 1;
	vector<RoomData> rooms;
};
void to_json(json& j, const GetRoomsResponse& response);


struct GetPlayersInRoomResponse
{
	vector<string> players;
};
void to_json(json& j, const GetPlayersInRoomResponse& response);


struct GetHighScoreResponse
{
	uint status = 1;
	vector<HighScoreRow> statistics;
};
void to_json(json& j, const GetHighScoreResponse& response);


struct GetPersonalStatsResponse
{
	uint status = 1;
	vector<string> statistics;
};
void to_json(json& j, const GetPersonalStatsResponse& response);


struct JoinRoomResponse
{
	uint status = 1;
};
void to_json(json& j, const JoinRoomResponse& response);


struct CreateRoomResponse
{
	uint status = 1;
	RoomData roomData;
};
void to_json(json& j, const CreateRoomResponse& response);


struct CheckIfUserExistsResponse
{
	bool exists = true;
	CheckIfUserExistsResponse(bool _exists) : exists(_exists) {}
};
void to_json(json& j, const CheckIfUserExistsResponse& response);


struct CloseRoomResponse
{
	uint status = 1;
};
void to_json(json& j, const CloseRoomResponse& response);


struct StartGameResponse
{
	uint status = 1;
};
void to_json(json& j, const StartGameResponse& response);


struct GetRoomStateResponse
{
	uint status = 1;
	RoomState roomState;
};
void to_json(json& j, const GetRoomStateResponse& response);


struct LeaveRoomResponse
{
	uint status = 1;
};
void to_json(json& j, const LeaveRoomResponse& response);


struct LeaveGameResponse
{
	uint status = 1;
};
void to_json(json& j, const LeaveGameResponse& response);


struct GetQuestionResponse
{
	uint status = 1;
	wstring question;
	vector<AnswerItem> answers;
	QuestionDifficulty difficulty;
};
void to_json(json& j, const GetQuestionResponse& response);


struct SubmitAnswerResponse
{
	uint status = 1;
	uint correctAnswerId = 0;
};
void to_json(json& j, const SubmitAnswerResponse& response);


struct GetGameResultResponse
{
	uint status;
	vector<PlayerResults> results;
};
void to_json(json& j, const GetGameResultResponse& response);
