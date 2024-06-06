#pragma once
#include <map>
#include "Room.h"

using std::map;

class RoomManager
{

private:
	map<uint, std::shared_ptr<Room>> m_rooms;

public:
	static uint roomID;
	static uint generateRoomID();
	void createRoom(std::shared_ptr<LoggedUser> host, RoomData& roomMetadata);
	void deleteRoom(uint roomId);
	RoomState getRoomState(uint roomId);
	RoomState getRoomState(Room& room);
	RoomStatus getRoomStatus(uint roomId);
	vector<RoomData> getRooms();
	Room& getRoom(uint roomId);
};

