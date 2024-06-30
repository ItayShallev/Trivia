#include "LoggedUser.h"


LoggedUser::LoggedUser(const string& username, const UserStatus& userStatus) : m_username(username), m_userStatus(userStatus) { }


string LoggedUser::getUserName() const
{
	return this->m_username;
}


UserStatus LoggedUser::getUserStatus() const
{
	return this->m_userStatus;
}


void LoggedUser::setUserStatus(const UserStatus& newUserStatus)
{
	this->m_userStatus = newUserStatus;
}


bool LoggedUser::operator==(const LoggedUser& other) const
{
	return this->m_username == other.m_username;
}


bool LoggedUser::operator==(const LoggedUser* other) const
{
	return this->m_username == other->m_username;
}
