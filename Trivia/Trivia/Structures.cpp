#include "Structures.h"

// ******************* RESPONSE STRUCTURES *******************
// ErrorResponse
void to_json(json& j, const ErrorResponse& response)
{
	j = json{ { "message", response.message } };
}


// LoginResponse
void to_json(json& j, const LoginResponse& response)
{
	j = json{ {"status", response.status} };
}


// SignupResponse
void to_json(json& j, const SignupResponse& response)
{
	j = json{ { "status", response.status } };
}


// LogoutResponse
void to_json(json& j, const LogoutResponse& response)
{
	j = json{ {"status", response.status} };
}


// GetRoomsResponse
void to_json(json& j, const GetRoomsResponse& response)
{
	j = json{ {"status", response.status}, {"rooms", response.rooms} };
}


// GetPlayersInRoomResponse
void to_json(json& j, const GetPlayersInRoomResponse& response)
{
	j = json{ {"players", response.players} };
}


// GetHighScoreResponse
void to_json(json& j, const GetHighScoreResponse& response)
{
	j = json{ {"status", response.status}, {"statistics", response.statistics} };
}


// GetPersonalStatsResponse
void to_json(json& j, const GetPersonalStatsResponse& response)
{
	j = json{ {"status", response.status}, {"statistics", response.statistics} };
}


// JoinRoomResponse
void to_json(json& j, const JoinRoomResponse& response)
{
	j = json{ {"status", response.status} };
}


// CreateRoomResponse
void to_json(json& j, const CreateRoomResponse& response)
{
	j = json{ {"status", response.status} };
}

// CheckIfUserExists
void to_json(json& j, const CheckIfUserExistsResponse& response)
{
	j = json{ {"exists", response.exists} };
}


// RoomData
void to_json(json& j, const RoomData& response)
{
	j = json{
		{"id", response.id},
		{"name", response.name},
		{"maxPlayers", response.maxPlayers},
		{"numOfQuestionsInGame", response.numOfQuestionsInGame},
		{"timePerQuestion", response.timePerQuestion},
		{"roomState", response.roomState}
	};
}
