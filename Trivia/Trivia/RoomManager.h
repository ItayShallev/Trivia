#pragma once
#include <map>
#include "Room.h"

using std::map;

class RoomManager
{

private:
	map<uint, Room*> m_rooms;
	static uint roomID;

public:
	RoomManager();
	static uint generateRoomID();
	void createRoom(LoggedUser& host, RoomData& roomMetadata);
	void deleteRoom(uint roomId);
	RoomState getRoomState(uint roomId);
	vector<RoomData> getRooms();
	Room& getRoom(uint roomId);
};

