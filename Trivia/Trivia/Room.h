#pragma once
#include "LoggedUser.h"
#include "Structures.h"

class Room
{
private:
	RoomData m_metadata;
	vector<std::shared_ptr<LoggedUser>> m_users;

public:
	Room(uint id);
	Room(const RoomData& metadata);
	void addUser(std::shared_ptr<LoggedUser> user);
	void removeUser(std::shared_ptr<LoggedUser> user);
	vector<string> getAllUsers();


	// setters
	void setName(const string name);
	void setMaxPlayers(const uint maxPlayers);
	void setNumOfQuestions(const uint numOfQuestions);
	void setTimePerQuestion(const uint timePerQuestion);
	void setRoomStatus(const RoomStatus state);

	// getters
	RoomData getRoomData();
	uint getID();
	string getName();
	string getAdmin();
	uint getMaxPlayers();
	uint getNumOfQuestions();
	uint getTimePerQuestion();
	RoomStatus getRoomStatus();

};

