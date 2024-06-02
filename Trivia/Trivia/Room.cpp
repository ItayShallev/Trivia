#include "Room.h"

using std::find;

Room::Room(uint id)
{
	// set the id
	this->m_metadata = {
		id,
		"",
		1,
		1,
		1,
		RoomStatus::Waiting
	};
}

Room::Room(const RoomData& metadata)
{
	this->m_metadata = metadata;
}

void Room::addUser(LoggedUser* user)
{
	// if there is room to add users
	if (m_users.size() < getMaxPlayers())
	{
		m_users.push_back(user);
	}
}

void Room::removeUser(LoggedUser* user)
{
	// remove the user from the vector
	auto userIndex = find(m_users.begin(), m_users.end(), user);
	m_users.erase(userIndex);
}

vector<string> Room::getAllUsers()
{
	// init the string vector
	vector<string> retVector;

	// iterate through the users
	for (LoggedUser* currUser : m_users)
	{
		// add the user name to the vector
		retVector.push_back(currUser->getUserName());
	}

	// return the vector
	return retVector;
}

void Room::setName(const string name)
{
	this->m_metadata.name = name;
}

void Room::setMaxPlayers(const uint maxPlayers)
{
	this->m_metadata.maxPlayers = maxPlayers;
}

void Room::setNumOfQuestions(const uint numOfQuestions)
{
	this->m_metadata.numOfQuestionsInGame = numOfQuestions;
}

void Room::setTimePerQuestion(const uint timePerQuestion)
{
	this->m_metadata.timePerQuestion = timePerQuestion;
}

void Room::setRoomStatus(const RoomStatus state)
{
	this->m_metadata.roomStatus = state;
}

RoomData Room::getRoomData()
{
	return this->m_metadata;
}

uint Room::getID()
{
	return this->m_metadata.id;
}

string Room::getName()
{
	return this->m_metadata.name;
}

uint Room::getMaxPlayers()
{
	return this->m_metadata.maxPlayers;
}

uint Room::getNumOfQuestions()
{
	return this->m_metadata.numOfQuestionsInGame;
}

uint Room::getTimePerQuestion()
{
	return this->m_metadata.timePerQuestion;
}

RoomStatus Room::getRoomStatus()
{
	return this->m_metadata.roomStatus;
}
