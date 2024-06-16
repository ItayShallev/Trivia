#pragma once

typedef unsigned int uint;

// ************************** SERVER CONSTANTS *************************
#define SERVER_PORT 8888
#define DEFAULT_BUFFER_SIZE 255
#define LIMIT_OF_MAX_PLAYERS_IN_ROOM 20



// ************************** ENUMS *************************
enum RequestId
{
	LogoutRequestId = 0,
	LoginRequestId,
	SignupRequestId,
	CreateRoomRequestId,
	GetRoomsRequestId,
	GetPlayersInRoomRequestId,
	JoinRoomRequestId,
	GetPersonalStatisticsRequestId,
	GetHighScoreRequestId,
	CheckIfUserExistsRequestId,
	CloseRoomRequestId,
	LeaveRoomRequestId,
	StartGameRequestId,
	GetRoomStateRequestId,
	SubmitAnswerRequestId,
	LeaveGameRequestId,
	GetQuestionRequestId,
	GetGameResultRequestId
};


enum ResponseId
{
	LogoutResponseId = 0,
	LoginResponseId,
	SignupResponseId,
	CreateRoomResponseId,
	GetRoomsResponseId,
	GetPlayersInRoomResponseId,
	JoinRoomResponseId,
	GetPersonalStatisticsResponseId,
	GetHighScoreResponseId,
	CheckIfUserExistsResponseId,
	CloseRoomResponseId,
	LeaveRoomResponseId,
	StartGameResponseId,
	GetRoomStateResponseId,
	SubmitAnswerResponseId,
	LeaveGameResponseId,
	GetQuestionResponseId,
	GetGameResultResponseId,
	ErrorResponseId
};

enum RoomStatus
{
	Waiting = 0,
	Playing,
	Closed
};

enum QuestionDifficulty
{
	Easy = 0,
	Medium,
	Hard
};



// ************************** PROTOCOL_CONSTANTS *************************
#define ID_BYTE_LENGTH			2

#define DATA_BYTE_LENGTH		4
#define DATA_BYTE_START_INDEX	2
#define DATA_BYTE_END_INDEX		5

#define DOZEN_MULTIPLIER		10





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
NUM_QUESTIONS_ANSWERED INTEGER NOT NULL,
NUM_CORRECT_ANSWERS INTEGER NOT NULL,
NUM_WRONG_ANSWERS INTEGER NOT NULL,
AVERAGE_ANSWER_TIME FLOAT NOT NULL,
POINTS INTEGER NOT NULL,
FOREIGN KEY (USERNAME) REFERENCES USERS(USERNAME));)"

#define QUESTIONS_TABLE_STARTING_ID		1
#define MAX_QUESTIONS_PER_REQUEST		50
#define TIMES_TO_REQUEST_QUESTIONS		4
#define TRIVIA_API_COOLDOWN				5

#define CORRECT_ANSWER_INDEX			1
#define INCORRECT_ANSWER_1_INDEX		2
#define INCORRECT_ANSWER_2_INDEX		3
#define INCORRECT_ANSWER_3_INDEX		4
#define DIFFICULTY_INDEX				5

#define TIME_EXPIRED_ANSWER_ID				4


// ************************** Game *************************
// Leaderboard
//#define LEADERBOARD_SIZE					5
#define LEADERBOARD_MIN_GAMES_TO_QUALIFY	1

#define WINS_WEIGHT							2
#define AVERAGE_ANSWER_TIME_WEIGHT			1

#define POINTS_POSSIBLE_FOR_EASY			100
#define POINTS_POSSIBLE_FOR_MEDIUM			350
#define POINTS_POSSIBLE_FOR_HARD			500


// ************************** Console Colors *************************
#define GREEN	2
#define WHITE	15
#define CYAN	3
#define GREY	7


// ************************** GENERAL *************************
#define BASE_10		10