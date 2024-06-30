#pragma once

#include "LoggedUser.h"
#include "GameStructures.h"


using std::shared_ptr;


class Room
{
private:
	RoomData m_metadata;
	vector<shared_ptr<LoggedUser>> m_users;

public:
	Room(uint id);
	Room(const RoomData& metadata);
	bool addUser(shared_ptr<LoggedUser> user);
	void removeUser(shared_ptr<LoggedUser> user);
	vector<string> getAllUsers() const;

	// setters
	void setName(const string& name);
	void setMaxPlayers(const uint maxPlayers);
	void setNumOfQuestions(const uint numOfQuestions);
	void setTimePerQuestion(const uint timePerQuestion);
	void setRoomStatus(const RoomStatus status);

	// getters
	vector<shared_ptr<LoggedUser>> getUsers() const;
	RoomData getRoomData() const;
	uint getId() const;
	string getName() const;
	string getAdmin() const;
	uint getMaxPlayers() const;
	uint getNumOfQuestions() const;
	uint getTimePerQuestion() const;
	RoomStatus getRoomStatus() const;
};
