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
	GetStatisticsRequestId,
	GetHighScoreRequestId,
	CheckIfUserExistsRequestId
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
	CreateRoomResponseId,
	CheckIfUserExistsResponseId
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
#define USERS_TABLE_SQL_STATEMENT R"(
CREATE TABLE USERS(USERNAME TEXT PRIMARY KEY NOT NULL,
PASSWORD TEXT NOT NULL,
MAIL TEXT NOT NULL);)"

#define QUESTIONS_TABLE_SQL_STATEMENT R"(
CREATE TABLE QUESTIONS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
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
NUM_GAMES_PLAYED INTEGER NOT NULL,
POINTS_EARNED INTERGER NOT NULL,
POINTS_LOST INTEGER NOT NULL,
NUM_GAMES_WON INTEGER NOT NULL,
NUM_GAMES_LOST INTEGER NOT NULL,
NUM_QUESTIONS_ANSWERED INTEGER NOT NULL,
NUM_CORRECT_ANSWERS INTEGER NOT NULL,
AVERAGE_ANSWER_TIME FLOAT NOT NULL,
NUM_ROOMS_CREATED INTEGER NOT NULL,
NUM_ROOMS_JOINED INTEGER NOT NULL,
FOREIGN KEY (USERNAME) REFERENCES USERS(USERNAME));)"




// ************************** Game *************************
// Leaderboard
#define LEADERBOARD_SIZE 5
#define LEADERBOARD_MIN_GAMES_TO_QUALIFY 5
#define WINS_WEIGHT 2
#define AVERAGE_ANSWER_TIME_WEIGHT 1