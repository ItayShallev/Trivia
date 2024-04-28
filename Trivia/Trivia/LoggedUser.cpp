#include "LoggedUser.h"


/**
 * @brief		Constructor, initializes a new LoggedUser instance
 * @param		username		The username to set to the new LoggedUser object
 */
LoggedUser::LoggedUser(const string& username) : m_username(username) { }


/**
 * @brief		Returns the username of the LoggedUser object
 * @return		The username of the LoggedUser object
 */
string LoggedUser::getUserName() const
{
	return this->m_username;
}
