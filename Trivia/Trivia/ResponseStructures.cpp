/**************************************************\
 * Converts response structures to JSON objects.  *
 * See Structures.h for structure definitions.    *
\**************************************************/
#include "ResponseStructures.h"


// RoomData
void to_json(json& j, const RoomData& response)
{
	j = json{
		{"id", response.id},
		{"name", response.name},
		{"admin", response.admin},
		{"maxPlayers", response.maxPlayers},
		{"numOfQuestionsInGame", response.numOfQuestionsInGame},
		{"timePerQuestion", response.timePerQuestion},
		{"roomStatus", response.roomStatus}
	};
}

// PlayerResults
void to_json(json& j, const PlayerResults& response)
{
	j = json{
		{"username", response.username},
		{"correctAnswerCount", response.correctAnswerCount},
		{"wrongAnswerCount", response.wrongAnswerCount},
		{"averageAnswerTime", std::round(response.averageAnswerTime * 100.0) / 100.0},
		{"points", response.points},
		{"rank", response.rank}
	};
}

// HighScoreRow
void to_json(json& j, const HighScoreRow& response)
{
	j = json{
		{"username", response.username},
		{"numGamesPlayed", response.numGamesPlayed},
		{"numCorrectAnswers", response.numCorrectAnswers},
		{"numWrongAnswers", response.numWrongAnswers},
		{"averageAnswerTime", std::round(response.averageAnswerTime * 100.0) / 100.0},
		{"points", response.points},
		{"rank", response.rank},
	};
}

// AnswerItem
void to_json(json& j, const AnswerItem& response)
{
	j = json{
	{"answerId", response.answerId},
	{"answer", response.answer},
	};
}


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
	j = json{
		{"status", response.status},
		{"roomData", response.roomData}
	};
}

// CheckIfUserExistsResponse
void to_json(json& j, const CheckIfUserExistsResponse& response)
{
	j = json{ {"exists", response.exists} };
}

// CloseRoomResponse
void to_json(json& j, const CloseRoomResponse& response)
{
	j = json{ {"status", response.status} };
}

// StartGameResponse
void to_json(json& j, const StartGameResponse& response)
{
	j = json{ {"status", response.status} };
}

// GetRoomStateResponse
void to_json(json& j, const GetRoomStateResponse& response)
{
	j = json{
		{"status", response.status},
		{"hasGameBegan", response.roomState.hasGameBegan},
		{"players", response.roomState.players},
		{"questionCount", response.roomState.questionCount},
		{"answerTimeout", response.roomState.answerTimeout},
		{"roomStatus", response.roomState.roomStatus}
	};
}

// LeaveRoomResponse
void to_json(json& j, const LeaveRoomResponse& response)
{
	j = json{ {"status", response.status} };
}

// LeaveGameResponse
void to_json(json& j, const LeaveGameResponse& response)
{
	j = json{ {"status", response.status} };
}

// GetQuestionResponse
void to_json(json& j, const GetQuestionResponse& response)
{
	j = json{
		{"status", response.status},
		{"question", response.question},
		{"answers", response.answers},
		{"difficulty", response.difficulty}
	};
}

// SubmitAnswerResponse
void to_json(json& j, const SubmitAnswerResponse& response)
{
	j = json{
	{"status", response.status},
	{"correctAnswerId", response.correctAnswerId},
	};
}

// GetGameResultResponse
void to_json(json& j, const GetGameResultResponse& response)
{
	j = json{
		{"status", response.status},
		{"playerResults", response.results}
	};
}
