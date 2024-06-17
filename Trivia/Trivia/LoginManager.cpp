#include "LoginManager.h"

using std::find_if;


/**
 * @brief	Constructor, Initializes a new LoginManager instance
 * @param	database		The database to set to the new LoginManager object
 * @param	loggedUsers		The logged users vector to set to the new LoginManager object (can be an empty vector)
 */
LoginManager::LoginManager(IDatabase* database, const vector<std::shared_ptr<LoggedUser>>& loggedUsers) : m_database(database), m_loggedUsers(loggedUsers) { }


/**
 * @brief	Signs up a new user (adds him to the DB)
 * @param	username	The username to set to the new user
 * @param	password	The password to set to the new user
 * @param	mail		The mail to set to the new user
 * @return	True if the user was successfully signed up, false otherwise
 */
bool LoginManager::signup(const string& username, const string& password, const string& mail)
{
	if (this->m_database->addNewUser(username, password, mail))
	{
		this->m_loggedUsers.emplace_back(std::make_shared<LoggedUser>(username));		// Adding the user to the logged users vector (emplace back constructs a new LoggedUser object automatically)

		return true;
	}

	return false;
}


/**
 * @brief	Logs an existing user to the system
 * @param	username	The username of the user to log to the system
 * @param	password	The password of the user to log to the system
 * @return	True if the user was successfully logged into the system, false otherwise
 */
bool LoginManager::login(const string& username, const string& password)
{
	// Checking if the user exists and checking if the given password matches to the user's
	if (this->m_database->doesUserExist(username) && this->m_database->doesPasswordMatch(username, password))
	{
		// Checking if the user already logged to the system
		for (auto userIterator = this->m_loggedUsers.begin(); userIterator != this->m_loggedUsers.end(); ++userIterator)
		{
			if ((*userIterator)->getUserName() == username)
			{
				return false;		// Cannot log into an account that already logged
			}
		}

		this->m_loggedUsers.emplace_back(std::make_shared<LoggedUser>(username));		// Adding the user to the logged users vector (emplace back constructs a new LoggedUser object automatically)
		return true;
	}

	return false;
}


/**
 * @brief	Logs a user out of the system
 * @param	username	The username of the user to log out of the system
 * @return	True if the user was successfully logged out of the system, false otherwise
 */
bool LoginManager::logout(const string& username)
{
	// Finding the user in the logged users vector that has the given username
	for (auto userIterator = this->m_loggedUsers.begin(); userIterator != this->m_loggedUsers.end(); ++userIterator)
	{
		if ((*userIterator)->getUserName() == username)
		{
			this->m_loggedUsers.erase(userIterator);		// Deleting the user from the logged users vector
			return true;
		}
	}

	return false;
}


/**
 * @brief	Checks if a user with a given username exists on the database
 * @param	username	The username of the user to check if exists on the database
 * @return	True if the user was exists, false otherwise
 */
bool LoginManager::doesUserExist(const string& username)
{
	return this->m_database->doesUserExist(username);
}
