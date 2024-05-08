#pragma once

// ************************** SERVER CONSTANTS *************************
#define SERVER_PORT 8888
#define DEFAULT_BUFFER_SIZE 255			// TODO: remove when message format is established, update receive data




// ************************** ENUMS *************************
enum RequestId
{
	LogoutRequestId = 0,
	LoginRequestId,
	SignupRequestId,
	MenuRequestId,
	CreateRoomRequestId,
	GetRoomRequestId,
	GetPlayersInRoomRequestId,
	JoinRoomRequestId,
	GetStatisticsRequestId
	

};


enum ResponseId
{
	LogoutResponseId = 0,
	LoginResponseId,
	SignupResponseId,
	ErrorResponseId,
	GetRoomsResponseId,
	GetPlayersInRoomResponseId,
	GetHighScoreResponseId,
	GetPersonalStatsResponseId,
	JoinRoomResponseId,
	CreateRoomResponseId
	
};

enum RoomState
{
	Waiting = 0,
	Playing = 1,
	Finished = 2 // future use?
};




// ************************** DE/SERIALIZERS *************************
#define DATA_BYTE_LENGTH 4





// ************************** Database *************************
#define USERS_TABLE_SQL_STATEMENT R"(CREATE TABLE USERS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
USERNAME TEXT NOT NULL,
PASSWORD TEXT NOT NULL,
MAIL TEXT NOT NULL);)"

#define QUESTIONS_TABLE_SQL_STATEMENT R"(CREATE TABLE QUESTIONS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
TYPE TEXT NOT NULL,
DIFFICULTY TEXT NOT NULL,
CATEGORY TEXT NOT NULL,
QUESTION TEXT NOT NULL,
CORRECT_ANSWER TEXT NOT NULL,
INCORRECT_ANSWER_1 TEXT NOT NULL,
INCORRECT_ANSWER_2 TEXT NOT NULL,
INCORRECT_ANSWER_3 TEXT NOT NULL);)"

#define STATISTICS_TABLE_SQL_STATEMENT R"(
CREATE TABLE STATISTICS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
USERNAME TEXT NOT NULL,
GAMES_PLAYED INTEGER NOT NULL,
POINTS_EARNED INTERGER NOT NULL,
POINTS_LOST INTEGER NOT NULL,
GAMES_WON INTEGER NOT NULL,
GAMES_LOST INTEGER NOT NULL,
QUESTIONS_ANSWERED INTEGER NOT NULL,
AVERGAE_ANSWER_TIME INTEGER NOT NULL,
ROOMS_CREATED INTEGER NOT NULL,
ROOMS_JOINED INTEGER NOT NULL);)"
