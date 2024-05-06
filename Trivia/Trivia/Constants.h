#pragma once

// ************************** SERVER CONSTANTS *************************
#define SERVER_PORT 8888
#define DEFAULT_BUFFER_SIZE 255			// TODO: remove when message format is established, update receive data




// ************************** ENUMS *************************
enum RequestId
{
	LoginRequestId = 0,
	SignupRequestId = 1,
	MenuRequestId = 2
};


enum ResponseId
{
	LoginResponseId = 0,
	SignupResponseId = 1,
	ErrorResponseId = 2
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
