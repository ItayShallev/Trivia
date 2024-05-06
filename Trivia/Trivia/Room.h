#pragma once
#include "LoggedUser.h"
#include "Structures.h"

class Room
{
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;

public:
	Room(uint id);
	Room(const RoomData& metadata);
	void addUser(LoggedUser& user);
	void removeUser(LoggedUser user);
	vector<string> getAllUsers();


	// setters
	void setName(const string name);
	void setMaxPlayers(const uint maxPlayers);
	void setNumOfQuestions(const uint numOfQuestions);
	void setTimePerQuestion(const uint timePerQuestion);
	void setRoomState(const RoomState state);

	// getters
	RoomData getRoomData();
	uint getID();
	string getName();
	uint getMaxPlayers();
	uint getNumOfQuestions();
	uint getTimePerQuestion();
	RoomState getRoomState();

};

