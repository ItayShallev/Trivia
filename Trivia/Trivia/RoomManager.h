#pragma once

#include <map>
#include "Room.h"


using std::map;
using std::shared_ptr;


class RoomManager
{
public:
	RoomManager() = default;

	static uint roomID;
	static uint generateRoomID();

	void createRoom(shared_ptr<LoggedUser> host, RoomData& roomMetadata);
	void deleteRoom(uint roomId);

	RoomState getRoomState(uint roomId);
	RoomState getRoomState(Room& room);
	RoomStatus getRoomStatus(uint roomId);
	vector<RoomData> getRooms();
	Room& getRoom(uint roomId);

private:
	map<uint, shared_ptr<Room>> m_rooms;
};
