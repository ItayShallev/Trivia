#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Constants.h"
#include "json.hpp"
#include "IRequestHandler.h"
#include "Question.h"


using std::string;
using std::vector;
using nlohmann::json;
using std::shared_ptr;


typedef vector<unsigned char> Buffer;
typedef unsigned int uint;


struct RequestInfo
{
	Buffer buffer;
	RequestId id;
	time_t ReceivalTime;
};


struct RequestResult
{
	Buffer response;
	shared_ptr<IRequestHandler> newHandler;
};


struct RoomState
{
	bool hasGameBegan;
	vector<string> players;
	uint questionCount;
	uint answerTimeout;
	RoomStatus roomStatus;
};


struct RoomData
{
	uint id;
	string name;
	string admin;
	uint maxPlayers;
	uint numOfQuestionsInGame;
	uint timePerQuestion;
	RoomStatus roomStatus;
};
void to_json(json& j, const RoomData& response);


struct PlayerResults
{
	string username;
	uint correctAnswerCount = 0;
	uint wrongAnswerCount = 0;
	double averageAnswerTime = 0.0;
	uint points = 0;
	uint rank = 0;
};
void to_json(json& j, const PlayerResults& response);


struct GameData
{
	Question currentQuestion;
	uint correctAnswerCount = 0;
	uint wrongAnswerCount = 0;
	double averageAnswerTime = 0.0;
	uint points = 0;

	bool leftGame = false;
};


struct HighScoreRow
{
	string username;
	uint numGamesPlayed = 0;
	uint numCorrectAnswers = 0;
	uint numWrongAnswers = 0;
	double averageAnswerTime = 0.0;
	uint points = 0;
	uint rank = 0;
};
void to_json(json& j, const HighScoreRow& response);