#include "Room.h"
#include <iostream>

using std::find;

Room::Room(uint id)
{
	// set the id
	this->m_metadata = {
		id,
		"",
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

void Room::addUser(std::shared_ptr<LoggedUser> user)
{
	// if there is room to add users
	if (m_users.size() < getMaxPlayers())
	{
		m_users.push_back(user);
	}
}

void Room::removeUser(std::shared_ptr<LoggedUser> user)
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
	for (std::shared_ptr<LoggedUser> currUser : m_users)
	{
		// add the username to the vector
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

vector<std::shared_ptr<LoggedUser>> Room::getUsers() const
{
	return this->m_users;
}

RoomData Room::getRoomData() const
{
	return this->m_metadata;
}

uint Room::getID() const
{
	return this->m_metadata.id;
}

string Room::getName() const
{
	return this->m_metadata.name;
}

string Room::getAdmin() const
{
	return this->m_metadata.admin;
}

uint Room::getMaxPlayers() const
{
	return this->m_metadata.maxPlayers;
}

uint Room::getNumOfQuestions() const
{
	return this->m_metadata.numOfQuestionsInGame;
}

uint Room::getTimePerQuestion() const
{
	return this->m_metadata.timePerQuestion;
}

RoomStatus Room::getRoomStatus() const
{
	return this->m_metadata.roomStatus;
}
