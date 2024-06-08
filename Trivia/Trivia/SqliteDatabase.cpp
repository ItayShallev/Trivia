#include "SqliteDatabase.h"
#include "Constants.h"
#include "Helper.h"
#include <iostream>
#include <io.h>
#include <set>


using std::string;
using std::set;
using std::to_string;
using std::cout;
using std::stoi;
using std::stof;


/**
 * @brief	Constructor, initializes the SqliteDatabase instance 
 * @param	databaseName		The name to give the database (will determine the .sqlite file name)
 */
SqliteDatabase::SqliteDatabase(const string& databaseName) : _databaseName(databaseName)
{
	this->open();
}


/**
 * @brief	Destructor, closes the Sqlite database and sets the db pointer to nullptr
 */
SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
}


/**
 * @brief		Executes an SQL statement/query on an Sqlite database
 * @param		statement			The statement/query to execute
 * @param		callbackFunction	The callback function to call for each result row
 * @param		callbackParam		The parameter for the callback function (The way of transmitting the SQL query result)
 * @return		A boolean value indicating whether the operation succeeded or not
 * @note		callbackFunction and callbackParam can be nullptr
 */
template<typename funcPtr>
bool SqliteDatabase::executeSqlStatement(const string& statement, const funcPtr callbackFunction, void* callbackParam)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->_db, statement.c_str(), callbackFunction, callbackParam, &errMessage);

	if (res != SQLITE_OK)
	{
		std::cout << "Failed to send the query:\n" << errMessage << "\n";
		this->close();

		return false;
	}

	return true;
}


/**
 * @brief		Initializes the Trivia database by creating necessary tables if they do not exist.
 * @return		True if the database was successfully initialized, false otherwise
 */
bool SqliteDatabase::initDatabase()
{
	string initStatement = string(USERS_TABLE_SQL_STATEMENT) + string(QUESTIONS_TABLE_SQL_STATEMENT) + string(STATISTICS_TABLE_SQL_STATEMENT);

	if (!this->executeSqlStatement(initStatement, nullptr, nullptr)) { return false; }

	// Adding questions to the DB
	system("python fetchQuestions.py");

	return true;
}


/**
 * @brief		Opens the Trivia database.
 * @return		True if the database was successfully opened (or initialized and then opened), false otherwise
 */
bool SqliteDatabase::open()
{
	// Checking if the file exists before trying to open it
	int doesFileExist = _access(this->_databaseName.c_str(), 0);

	// Opening the DB
	int res = sqlite3_open(this->_databaseName.c_str(), &this->_db);
	if (res != SQLITE_OK)
	{
		this->_db = nullptr;
		cout << "Failed to open DB\n";

		return false;
	}

	if (doesFileExist != 0)			// If the DB doesn't exist
	{
		// Creating the DB tables
		this->initDatabase();

		cout << "DB created!\n";
	}
	else
	{
		cout << "DB Exists...\n";
	}

	return true;
}


/**
 * @brief			Closes the Trivia database
 * @return			Void
 */
bool SqliteDatabase::close()
{
	int res = sqlite3_close(this->_db);

	// Checking if the DB was closed successfully
	if (res == SQLITE_OK)
	{
		this->_db = nullptr;
		cout << "The DB was closed successfully\n";

		return true;
	}

	return false;		// If the program reaches here - the DB has failed to close (shouldn't occur)
}


/**
 @brief		Callback function for checking the result-rows-count to figure out if a given user exists
 @param		data			A pointer to a boolean variable where the answer to the "question" will be stored
 @param		argc			The number of columns in the result set
 @param		argv			An array of strings representing the result set
 @param		azColName		An array of strings containing the column names of the result set
 @return	Always returns 0
 */
int SqliteDatabase::doesUserExistsCallback(void* data, int argc, char** argv, char** azColName)
{
	*(static_cast<bool*>(data)) = std::stoi(argv[0]) != 0;

	return 0;
}


/**
 @brief		Checks if a given user exists on the database
 @param		username			The username of the user to check if exists on the database
 @return	True if the user exists, false otherwise
 */
bool SqliteDatabase::doesUserExist(const string& username)
{
	string doesUserExistsQuery = R"(
					BEGIN TRANSACTION;
					
					SELECT COUNT(*) FROM USERS
					WHERE USERNAME = ')" + username + R"(';
					
					END TRANSACTION;
					)";

	bool doesUserExist = false;
	executeSqlStatement(doesUserExistsQuery, doesUserExistsCallback, &doesUserExist);

	return doesUserExist;
}


/**
 * @brief		Callback function for finding the password of an existing user on the database
 * @param		data			A pointer to a string where the user's password will be stored
 * @param		argc			The number of columns in the result set
 * @param		argv			An array of strings representing the result set
 * @param		azColName		An array of strings containing the column names of the result set
 * @return		Always returns 0
 */
int SqliteDatabase::doesPasswordMatchCallback(void* data, int argc, char** argv, char** azColName)
{
	*(static_cast<string*>(data)) = argv[0];

	return 0;
}


/**
 * @brief		Checks if a given user's password matches to the one that is stored in the database
 * @param		username	The username of the user to check if the given password matches his
 * @param		password	The password to check if matches to the one that's stored in the database
 * @return		True if the given password matches, false otherwise
 */
bool SqliteDatabase::doesPasswordMatch(const string& username, const string& password)
{
	string doesPasswordMatchQuery = R"(
					BEGIN TRANSACTION;
					
					SELECT PASSWORD FROM USERS
					WHERE USERNAME = ')" + username + R"(';
					
					END TRANSACTION;
					)";

	string userPassword;
	executeSqlStatement(doesPasswordMatchQuery, doesPasswordMatchCallback, &userPassword);

	return password == userPassword;
}


/**
 * @brief		Adds a new user record to the USERS table
 * @param		username	The username to set in the new record
 * @param		password	The password to set in the new record
 * @param		mail		The mail to set in the new record
 * @return		Always returns true
 */
bool SqliteDatabase::addNewUser(const string& username, const string& password, const string& mail)
{
	if (this->doesUserExist(username)) return false;

	string addNewUserStatement = R"(
					BEGIN TRANSACTION;

					INSERT INTO USERS
					(USERNAME, PASSWORD, MAIL)
					VALUES (')" + username + "', '" + password + "', '" + mail + R"(');
					
					END TRANSACTION;
					)";

	executeSqlStatement(addNewUserStatement, nullptr, nullptr);

	return true;
}


/**
 * @brief		Callback function that returns the result of a select query in an integer
 * @param		data			A pointer to an integer where the result will be stored
 * @param		argc			The number of columns in the result set
 * @param		argv			An array of strings representing the result set
 * @param		azColName		An array of strings containing the column names of the result set
 * @return	Always returns 0
 */
int SqliteDatabase::intCallback(void* data, int argc, char** argv, char** azColName)
{
	*(static_cast<int*>(data)) = stoi(argv[0]);

	return 0;
}


/**
 * @brief		Callback function that returns the result of a select query in an float
 * @param		data			A pointer to an integer where the result will be stored
 * @param		argc			The number of columns in the result set
 * @param		argv			An array of strings representing the result set
 * @param		azColName		An array of strings containing the column names of the result set
 * @return	Always returns 0
 */
int SqliteDatabase::floatCallback(void* data, int argc, char** argv, char** azColName)
{
	*(static_cast<float*>(data)) = stof(argv[0]);

	return 0;
}



/**
 * brief	Returns the average answer time of a given user
 * param	username		The username of the user to get its average answer time
 * return	The average answer time of the given user
 */
float SqliteDatabase::getPlayerAverageAnswerTime(const string& username)
{
	string statement = R"(
					BEGIN TRANSACTION;
					
					SELECT AVERAGE_ANSWER_TIME FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
					
					END TRANSACTION;
					)";
	
	float answerTime = 0;
	executeSqlStatement(statement, floatCallback, &answerTime);

	return answerTime;
}


/**
 * brief	Returns the number of correct answers of the given user
 * param	username	The username of the user to get its number of correct answers
 * return	The number of correct answers of the given user
 */
int SqliteDatabase::getNumOfCorrectAnswers(const string& username)
{
	const string statement = R"(
					BEGIN TRANSACTION;
					
					SELECT NUM_CORRECT_ANSWERS FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
					
					END TRANSACTION;
					)";

	int correctAnswers = 0;
	executeSqlStatement(statement, intCallback, &correctAnswers);

	return correctAnswers;
}


/**
 * brief	Returns the total number of answers the given user has answered
 * param	username	The username of the user to get its number of total answers
 * return	The number of total answers the given user has answered
 */
int SqliteDatabase::getNumOfTotalAnswers(const string& username)
{
	const string statement = R"(
					BEGIN TRANSACTION;
					
					SELECT NUM_QUESTIONS_ANSWERED FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
					
					END TRANSACTION;
					)";

	int numQuestionsAnswered = 0;
	executeSqlStatement(statement, intCallback, &numQuestionsAnswered);
	return numQuestionsAnswered;
}


/**
 * brief	Returns the number of games the given user has played
 * param	username	The username of the user to get its number of played games
 * return	The number of games the given user has played
 */
int SqliteDatabase::getNumOfPlayerGames(const string& username)
{
	const string statement = R"(
					BEGIN TRANSACTION;
					
					SELECT NUM_GAMES_PLAYED FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
					
					END TRANSACTION;
					)";

	int numOfPlayerGames = 0;
	executeSqlStatement(statement, intCallback, &numOfPlayerGames);

	return numOfPlayerGames;
}



/**
 * brief	Returns the score that the given user has earned
 * param	username	The username of the user to get its score
 * return	The score of the given user
 */
int SqliteDatabase::getPlayerScore(const string& username)
{
	const string statement = R"(
					BEGIN TRANSACTION;
					
					SELECT POINTS_EARNED FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
					
					END TRANSACTION;
					)";

	int numOfPlayerPoints = 0;
	executeSqlStatement(statement, intCallback, &numOfPlayerPoints);

	return numOfPlayerPoints;
}


/**
 * @brief	Returns the statistics of the user with the given username
 * @param	username		The username of the user to get its statistics
 * @return	A vector containing the user all-time statistics
 */
vector<string> SqliteDatabase::getUserStatistics(const string& username)
{
	vector<string> userStatistics;

	userStatistics.push_back(to_string(this->getPlayerScore(username)));					// Points earned
	userStatistics.push_back(to_string(this->getNumOfPlayerGames(username)));			// Number of Games Played
	userStatistics.push_back(to_string(this->getNumOfCorrectAnswers(username)));			// Number of Correct Answers
	userStatistics.push_back(to_string(this->getPlayerAverageAnswerTime(username)));		// Average Answer Time

	return userStatistics;
}


int SqliteDatabase::getHighScoresCallback(void* data, int argc, char** argv, char** azColName)
{
	(static_cast<vector<string>*>(data))->push_back(argv[0]);		// Pushing the username of the current user in the leaderboard into the vector

	return 0;
}


/**
 * @brief	Returns a leaderboard containing the 5 best users
 * @return	A vector containing the usernames of the 5 best users
 */
vector<string> SqliteDatabase::getHighScores()
{
	const string statement = R"(
					BEGIN TRANSACTION;
					
					SELECT
					USERNAME,
					(NUM_GAMES_WON / NUM_GAMES_PLAYED) * )" + to_string(WINS_WEIGHT) + R"( As WinRate,
					(1 - (NUM_GAMES_WON / NUM_GAMES_PLAYED)) * (1.0 / AVERAGE_ANSWER_TIME) * )" + to_string(AVERAGE_ANSWER_TIME_WEIGHT) + R"( AS LeaderboardScore
					FROM STATISTICS
					WHERE NUM_GAMES_PLAYED >= )" + to_string(LEADERBOARD_MIN_GAMES_TO_QUALIFY) + R"(
					GROUP BY USERNAME
					ORDER BY LeaderboardScore DESC
					LIMIT )" + to_string(LEADERBOARD_SIZE) + R"(;

					END TRANSACTION;
					)";

	vector<string> highScores;
	executeSqlStatement(statement, getHighScoresCallback, &highScores);

	return highScores;
}


/**
 * @brief	Callback function for getting a question from the database
 * @return	0 (indicates success)
 */
int SqliteDatabase::getQuestionCallback(void* data, int argc, char** argv, char** azColName)
{
	Question* question = static_cast<Question*>(data);

	// Setting the question text
	question->setQuestion(argv[0]);

	// Shuffling the possible answers
	vector<string> possibleAnswers{ argv[CORRECT_ANSWER_INDEX],argv[INCORRECT_ANSWER_1_INDEX],
									argv[INCORRECT_ANSWER_2_INDEX], argv[INCORRECT_ANSWER_3_INDEX] };
	int correctAnswerId = Helper::shuffleAnswers(possibleAnswers, argv[CORRECT_ANSWER_INDEX]);

	// Setting the possible answers
	question->setPossibleAnswers(possibleAnswers);

	// Setting the correct answerId
	question->setCorrectAnswerId(correctAnswerId);

	return 0;
}


/**
 * @brief	Returns the question with the given id from the database
 * @param	questionId		The id of the question to retrieve from the database
 * @return	The question with the given question id
 */
Question SqliteDatabase::getQuestion(const int& questionId)
{
	const string statement = R"(
					BEGIN TRANSACTION;
					
					SELECT QUESTION, CORRECT_ANSWER, INCORRECT_ANSWER_1, INCORRECT_ANSWER_2, INCORRECT_ANSWER_3
					FROM QUESTIONS
					WHERE ID = )" + to_string(questionId) + R"(;
					
					END TRANSACTION;
					)";

	Question question;
	executeSqlStatement(statement, getQuestionCallback, &question);

	return question;
}


/**
 * @brief	Returns a vector of random and unique questions from the database
 * @param	numberOfQuestions		The amount of questions to get from the database
 * @return	A vector with the wanted amount of questions
 */
vector<Question> SqliteDatabase::getRandomQuestions(const uint& numberOfQuestions)
{
	set<int> questionsIds = Helper::generateRandomNumbersSet(numberOfQuestions, QUESTIONS_TABLE_STARTING_ID, NUM_OF_QUESTIONS_IN_DB);

	vector<Question> questions;
	for (int questionId : questionsIds)
	{
		questions.push_back(this->getQuestion(questionId));
	}

	return questions;
}
