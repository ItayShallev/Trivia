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
	vector<std::shared_ptr<LoggedUser>> getUsers() const;
	RoomData getRoomData() const;
	uint getID() const;
	string getName() const;
	string getAdmin() const;
	uint getMaxPlayers() const;
	uint getNumOfQuestions() const;
	uint getTimePerQuestion() const;
	RoomStatus getRoomStatus() const;

};

