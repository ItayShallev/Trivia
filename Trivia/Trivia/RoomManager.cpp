#include "RoomManager.h"

using std::pair;
uint RoomManager::roomID = 0;


uint RoomManager::generateRoomID()
{
	// save the current room id value
	uint retRoomID = roomID;

	// increment the room id
	roomID++;

	// return the room id value that was stored
	return retRoomID;
}

void RoomManager::createRoom(LoggedUser& host, RoomData& roomMetadata)
{
	// create a new room with the metadata
	Room* newRoom = new Room(roomMetadata);

	// add the host
	newRoom->addUser(host);

	// insert the room into the map
	this->m_rooms.insert(pair<uint, Room*>(roomMetadata.id, newRoom));
}

void RoomManager::deleteRoom(uint roomId)
{
	// delete the room from the map
	this->m_rooms.erase(roomId);
}

RoomStatus RoomManager::getRoomStatus(uint roomId)
{
	// return the room status
	return m_rooms[roomId]->getRoomStatus();
}

vector<RoomData> RoomManager::getRooms()
{
	// init an empty vector
	vector<RoomData> rooms;

	// predetermine the size of the vector (runtime efficient)
	rooms.reserve(m_rooms.size());

	// iterate through the map
	for (auto& room : m_rooms)
	{
		// add the room data to the vector
		rooms.push_back(room.second->getRoomData());
	}

	// return the rooms
	return rooms;
}

Room& RoomManager::getRoom(uint roomId)
{
	// return the room
	return *m_rooms[roomId];
}
