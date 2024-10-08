#include "SqliteDatabase.h"
#include <iostream>
#include <io.h>
#include <set>
#include <thread>
#include <codecvt>
#include "Constants.h"
#include "Helper.h"
#include "GameStructures.h"


using std::string;
using std::wstring;
using std::set;
using std::pair;
using std::thread;
using std::to_string;
using std::cout;
using std::cerr;
using std::stoi;
using std::stof;
using std::wstring_convert;
using std::codecvt_utf8;


SqliteDatabase::SqliteDatabase(const string& databaseName) : _databaseName(databaseName)
{
	this->open();
}


SqliteDatabase::~SqliteDatabase()
{
	// Closing the database handle
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
		cout << "Failed to send the query:\n" << errMessage << "\n";
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

	// Adding questions to the DB from another thread to avoid blocking the main thread
	thread fetchQuestionsThread(fetchQuestion);
	fetchQuestionsThread.detach();

	return true;
}


/**
 * @brief		Runs a python script that fetches questions from a web API
 * @return		Void
 */
void SqliteDatabase::fetchQuestion()
{
	string command = "python fetchQuestions.py " + to_string(TIMES_TO_REQUEST_QUESTIONS);
	system(command.c_str());
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

	// Checking if the DB doesn't exist
	if (doesFileExist != 0)
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


bool SqliteDatabase::close()
{
	// Trying to close the DB
	int res = sqlite3_close(this->_db);

	// Checking if the DB was closed successfully
	if (res == SQLITE_OK)
	{
		this->_db = nullptr;
		cout << "The DB was closed successfully\n";

		return true;
	}

	return false;		// (If the program reaches here - the DB has failed to close (shouldn't occur))
}


int SqliteDatabase::doesUserExistCallback(void* data, int argc, char** argv, char** azColName)
{
	// Setting the DB result in the passed object
	*(static_cast<bool*>(data)) = stoi(argv[0]) != 0;

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
					SELECT COUNT(*) FROM USERS
					WHERE USERNAME = ')" + username + R"(';
					)";

	bool doesUserExist = false;
	executeSqlStatement(doesUserExistsQuery, doesUserExistCallback, &doesUserExist);

	return doesUserExist;
}


int SqliteDatabase::doesPasswordMatchCallback(void* data, int argc, char** argv, char** azColName)
{
	// Setting the DB result in the passed object
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
					SELECT PASSWORD FROM USERS
					WHERE USERNAME = ')" + username + R"(';
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

	// Adding a new statistics record for the user in the STATISTICS table
	addUserStatisticsRecord(username);

	return true;
}


int SqliteDatabase::intCallback(void* data, int argc, char** argv, char** azColName)
{
	// Setting the DB result in the passed object
	*(static_cast<int*>(data)) = stoi(argv[0]);

	return 0;
}


int SqliteDatabase::floatCallback(void* data, int argc, char** argv, char** azColName)
{
	// Setting the DB result in the passed object
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
					SELECT AVERAGE_ANSWER_TIME FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
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
uint SqliteDatabase::getNumOfCorrectAnswers(const string& username)
{
	const string statement = R"(
					SELECT NUM_CORRECT_ANSWERS FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
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
uint SqliteDatabase::getNumOfTotalAnswers(const string& username)
{
	const string statement = R"(
					SELECT NUM_QUESTIONS_ANSWERED FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
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
uint SqliteDatabase::getNumOfPlayerGames(const string& username)
{
	const string statement = R"(
					SELECT NUM_GAMES_PLAYED FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
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
uint SqliteDatabase::getPlayerScore(const string& username)
{
	const string statement = R"(
					SELECT POINTS FROM STATISTICS
					WHERE USERNAME = ')" + username + R"(';
					)";

	int numOfPlayerPoints = 0;
	executeSqlStatement(statement, intCallback, &numOfPlayerPoints);

	return numOfPlayerPoints;
}


int SqliteDatabase::getUserStatisticsCallback(void* data, int argc, char** argv, char** azColName)
{
	HighScoreRow* highScores = static_cast<HighScoreRow*>(data);
	char* end;

	int x = strtoul(argv[6], &end, BASE_10);

	// Setting the DB result in the passed object
	*highScores = { argv[0],								// Username
					strtoul(argv[1], &end, BASE_10),		// Number of games played
					strtoul(argv[2], &end, BASE_10),		// Number of correct answers
					strtoul(argv[3], &end, BASE_10),		// Number of wrong answers
					strtod(argv[4], &end),					// Average answer timer
					strtoul(argv[5], &end, BASE_10),		// points
					strtoul(argv[6], &end, BASE_10) };		// Rank

	return 0;
}


/**
 * @brief	Returns the statistics of the user with the given username
 * @param	username		The username of the user to get its statistics
 * @return	A vector containing the user all-time statistics
 */
HighScoreRow SqliteDatabase::getUserStatistics(const string& username)
{
	const string statement = R"(
					WITH RankedScores AS (
						SELECT
						USERNAME, NUM_GAMES_PLAYED, NUM_CORRECT_ANSWERS, NUM_WRONG_ANSWERS, AVERAGE_ANSWER_TIME, POINTS,
						ROW_NUMBER() OVER (ORDER BY POINTS DESC, AVERAGE_ANSWER_TIME ASC) as rank
						FROM STATISTICS
						WHERE NUM_GAMES_PLAYED >= )" + to_string(LEADERBOARD_MIN_GAMES_TO_QUALIFY) + R"(
					)

					SELECT * FROM RankedScores
					WHERE USERNAME = ')" + username + R"('
					ORDER BY rank;
					)";

	HighScoreRow userStatistics;

	executeSqlStatement(statement, getUserStatisticsCallback, &userStatistics);

	return userStatistics;
}


int SqliteDatabase::getHighScoresCallback(void* data, int argc, char** argv, char** azColName)
{
	vector<HighScoreRow>* highScores = static_cast<vector<HighScoreRow>*>(data);
	char* end;

	// Setting the DB result in the passed object
	HighScoreRow highScoreRow{ argv[0],									// Username
								strtoul(argv[1], &end, BASE_10),		// Number of games played
								strtoul(argv[2], &end, BASE_10),		// Number of correct answers
								strtoul(argv[3], &end, BASE_10),		// Number of wrong answers
								strtod(argv[4], &end),					// Average answer timer
								strtoul(argv[5], &end, BASE_10),		// points
								strtoul(argv[6], &end, BASE_10) };		// Rank

	highScores->push_back(highScoreRow);

	return 0;
}


/**
 * @brief	Returns a leaderboard of the best users
 * @return	A vector containing the usernames of the best users
 */
vector<HighScoreRow> SqliteDatabase::getHighScores()
{
	const string statement = R"(
					SELECT
					USERNAME, NUM_GAMES_PLAYED, NUM_CORRECT_ANSWERS, NUM_WRONG_ANSWERS, AVERAGE_ANSWER_TIME, POINTS,
					ROW_NUMBER() OVER (ORDER BY POINTS DESC, AVERAGE_ANSWER_TIME ASC) as rank
					FROM STATISTICS
					WHERE NUM_GAMES_PLAYED >= )" + to_string(LEADERBOARD_MIN_GAMES_TO_QUALIFY) + R"(

					ORDER BY POINTS DESC, AVERAGE_ANSWER_TIME ASC
					LIMIT )" + to_string(LEADERBOARD_SIZE) + R"(;
					)";

	vector<HighScoreRow> highScores;
	executeSqlStatement(statement, getHighScoresCallback, &highScores);

	return highScores;
}


void SqliteDatabase::addUserStatisticsRecord(const string& username)
{
	// Creating a record in the STATISTICS table for the user
	const string createUserRecordStatement = R"(
									    BEGIN TRANSACTION;

									    INSERT INTO STATISTICS
									    (USERNAME, NUM_GAMES_PLAYED, NUM_QUESTIONS_ANSWERED, 
									     NUM_CORRECT_ANSWERS, NUM_WRONG_ANSWERS, AVERAGE_ANSWER_TIME, POINTS)
									    VALUES (')" + username + R"(', 0, 0, 0, 0, 0.0, 0);

									    END TRANSACTION;
									)";

	// Executing the statement
	executeSqlStatement(createUserRecordStatement, nullptr, nullptr);
}


void SqliteDatabase::submitUserGameStatistics(const pair<shared_ptr<LoggedUser>, GameData>& user)
{
	GameData userGameData = user.second;

	uint numQuestionsAnsweredThisGame = userGameData.correctAnswerCount + userGameData.wrongAnswerCount;
	double totalAnswerTimeThisGame = userGameData.averageAnswerTime * numQuestionsAnsweredThisGame;

	string statement = R"(
					BEGIN TRANSACTION;

					UPDATE STATISTICS
					SET NUM_GAMES_PLAYED = NUM_GAMES_PLAYED + 1,
					NUM_CORRECT_ANSWERS = NUM_CORRECT_ANSWERS + )" + to_string(userGameData.correctAnswerCount) + R"(,
					NUM_WRONG_ANSWERS = NUM_WRONG_ANSWERS + )" + to_string(userGameData.wrongAnswerCount) + R"(,
					AVERAGE_ANSWER_TIME = ((AVERAGE_ANSWER_TIME * NUM_QUESTIONS_ANSWERED) + )" + to_string(totalAnswerTimeThisGame) + ")"
											"/ (NUM_QUESTIONS_ANSWERED + " + to_string(numQuestionsAnsweredThisGame) + R"(),
					NUM_QUESTIONS_ANSWERED = NUM_QUESTIONS_ANSWERED + )" + to_string(numQuestionsAnsweredThisGame) + R"(,
					POINTS = POINTS + )" + to_string(userGameData.points) + R"(

					WHERE USERNAME = ')" + user.first->getUserName() + R"(';
					
					END TRANSACTION;
					)";

	executeSqlStatement(statement, nullptr, nullptr);
}


void SqliteDatabase::submitGameStatistics(const map<shared_ptr<LoggedUser>, GameData>& users)
{
	// Iterating over all the players and submitting their game statistics
	for (auto user : users)
	{
		// Updating the statistics only for the players who finished the game
		if (!user.second.leftGame)
		{
			const string currentUsername = user.first->getUserName();

			// Modifying the user's record at the STATISTICS table
			submitUserGameStatistics(user);
		}
	}
}


bool SqliteDatabase::compileSqliteStatement(sqlite3_stmt*& statement, const string& query) const
{
	// compiling the SQL statement
	if (sqlite3_prepare_v2(this->_db, query.c_str(), -1, &statement, nullptr) != SQLITE_OK)
	{
		cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->_db) << '\n';

		sqlite3_close(this->_db);

		return false;
	}

	return true;
}


vector<Question> SqliteDatabase::processGetQuestionsResults(sqlite3_stmt* statement)
{
	vector<Question> questions;

	wstring_convert<codecvt_utf8<wchar_t>> utf8ToWstringConverter;

	while (sqlite3_step(statement) == SQLITE_ROW)		// Iterating over all the result rows
	{
		Question newQuestion;

		// Setting the question string
		string question = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

		// Converting the question from UTF-8 to wide string (to support special character displaying)
		wstring wideStringQuestion = utf8ToWstringConverter.from_bytes(question);
		newQuestion.setQuestion(wideStringQuestion);

		// Creating AnswerItems vector and setting an ID for each answer
		vector<AnswerItem> possibleAnswers;
		for (int i = CORRECT_ANSWER_INDEX; i <= INCORRECT_ANSWER_3_INDEX; ++i)
		{
			string currentAnswer = reinterpret_cast<const char*>(sqlite3_column_text(statement, i));

			// Converting the current answer from UTF-8 to wide string (to support special character displaying)
			wstring wideStringAnswer = utf8ToWstringConverter.from_bytes(currentAnswer);

			possibleAnswers.push_back(AnswerItem(i - 1, wideStringAnswer));
		}

		// Setting the possible answers
		newQuestion.setPossibleAnswers(possibleAnswers);

		// Setting the correct answer id
		newQuestion.setCorrectAnswerId(0);

		// Setting the question difficulty
		string stringQuestionDifficulty = reinterpret_cast<const char*>(sqlite3_column_text(statement, DIFFICULTY_INDEX));
		newQuestion.setDifficulty(Question::getDifficultyFromString(stringQuestionDifficulty));

		questions.push_back(newQuestion);
	}

	return questions;
}


vector<Question> SqliteDatabase::getRandomQuestions(const uint& numberOfQuestions)
{
	// Generating a random set of numbers that will be used to fetch questions from the DB
	set<int> questionsIds = Helper::generateRandomNumbersSet(numberOfQuestions, QUESTIONS_TABLE_STARTING_ID, TIMES_TO_REQUEST_QUESTIONS * MAX_QUESTIONS_PER_REQUEST);

	// Constructing the query with placeholders for the question ids
	string query = "SELECT QUESTION, CORRECT_ANSWER, INCORRECT_ANSWER_1, INCORRECT_ANSWER_2, INCORRECT_ANSWER_3, DIFFICULTY FROM QUESTIONS WHERE ID IN (";
	for (auto it = questionsIds.begin(); it != questionsIds.end(); ++it)
	{
		if (it != questionsIds.begin())
		{
			query += ", ";
		}
		query += "?";		// A placeholder that will be used to fill in question ids
	}
	query += ");";

	sqlite3_stmt* statement = nullptr;

	// compiling the SQL statement
	if (!compileSqliteStatement(statement, query)) { return { }; }

	// Binding the question ids to the prepared statement
	int index = 1;
	for (int id : questionsIds)
	{
		if (sqlite3_bind_int(statement, index, id) != SQLITE_OK)
		{
			cerr << "Failed to bind parameter: " << sqlite3_errmsg(this->_db) << '\n';

			sqlite3_finalize(statement);			// Destroying the prepared SQL statement
			sqlite3_close(this->_db);

			return { };
		}
		++index;
	}

	// Executing the statement and inserting the results into the questions vector
	vector<Question> questions = processGetQuestionsResults(statement);

	// Finalize the statement
	if (sqlite3_finalize(statement) != SQLITE_OK)
	{
		cerr << "Failed to finalize statement: " << sqlite3_errmsg(this->_db) << '\n';
	}

	return questions;
}
