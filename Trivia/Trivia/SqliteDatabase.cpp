#include "SqliteDatabase.h"
#include "Constants.h"
#include <iostream>
#include <io.h>


using std::cout;


/**
 * @brief	Constructor, initializes the SqliteDatabase instance 
 * @param	databaseName		The name to give the database (will determine the .sqlite file name)
 */
SqliteDatabase::SqliteDatabase(const string& databaseName) : _databaseName(databaseName)
{
	/*sqlite3_open(this->_databaseName.c_str(), &this->_db);*/
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
 @brief		Executes an SQL statement/query on an Sqlite database
 @param		statement			The statement/query to execute
 @param		callbackFunction	The callback function to call for each result row
 @param		callbackParam		The parameter for the callback function (The way of transmitting the SQL query result)
 @return	A boolean value indicating whether the operation succeeded or not
 @note		callbackFunction and callbackParam can be nullptr
 */
template<typename funcPtr>
bool SqliteDatabase::executeSqlStatement(const std::string& statement, const funcPtr callbackFunction, void* callbackParam)
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
	std::string initStatement = string(USERS_TABLE_SQL_STATEMENT) + string(QUESTIONS_TABLE_SQL_STATEMENT);

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
 @brief			Closes the Trivia database
 @return		Void
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
	std::string doesUserExistsQuery = R"(
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
 @brief		Callback function for finding the password of an existing user on the database
 @param		data			A pointer to a string where the user's password will be stored
 @param		argc			The number of columns in the result set
 @param		argv			An array of strings representing the result set
 @param		azColName		An array of strings containing the column names of the result set
 @return	Always returns 0
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
	std::string doesPasswordMatchQuery = R"(
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

	std::string addNewUserStatement = R"(
					BEGIN TRANSACTION;

					INSERT INTO USERS
					(USERNAME, PASSWORD, MAIL)
					VALUES (')" + username + "', '" + password + "', '" + mail + R"(');
					
					END TRANSACTION;
					)";

	executeSqlStatement(addNewUserStatement, nullptr, nullptr);

	return true;
}
