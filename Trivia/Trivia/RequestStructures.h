#pragma once

#include <string>


using std::string;


typedef unsigned int uint;


struct LoginRequest
{
	string username;
	string password;
};


struct SignupRequest
{
	string username;
	string password;
	string mail;
};


struct GetPlayersInRoomRequest
{
	uint roomID;
};


struct JoinRoomRequest
{
	uint roomID;
};


struct CreateRoomRequest
{
	string admin;
	string roomName;
	uint maxPlayers;
	uint questionCount;
	uint answerTimeout;
};


struct CheckIfUserExistsRequest
{
	string username;
};


struct CloseRoomRequest
{
	uint roomId;
};


struct StartGameRequest
{
	uint roomId;
};


struct SubmitAnswerRequest
{
	uint answerId;
	double answerTime;
};
