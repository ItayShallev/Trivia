#include "RoomManager.h"


using std::unique_ptr;
using std::make_unique;
using std::move;
using std::make_pair;


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


void RoomManager::createRoom(shared_ptr<LoggedUser> host, RoomData& roomMetadata)
{
	// create a new room with the metadata
	unique_ptr<Room> newRoom = make_unique<Room>(roomMetadata);

	// add the host
	newRoom->addUser(host);

	// inserting the room into the map, transferring the room ownership to m_rooms
	this->m_rooms.insert(make_pair(roomMetadata.id, move(newRoom)));
}


void RoomManager::deleteRoom(uint roomId)
{
	// delete the room from the map
	this->m_rooms.erase(roomId);
}


RoomState RoomManager::getRoomState(uint roomId)
{
	// get the room
	Room& room = getRoom(roomId);

	// build and return the room state
	return {
		room.getRoomStatus() == RoomStatus::Playing,
		room.getAllUsers(),
		room.getNumOfQuestions(),
		room.getTimePerQuestion(),
		room.getRoomStatus()
	};
}


RoomState RoomManager::getRoomState(Room& room)
{
	// build and return the room state
	return {
		room.getRoomStatus() == RoomStatus::Playing,
		room.getAllUsers(),
		room.getNumOfQuestions(),
		room.getTimePerQuestion(),
		room.getRoomStatus()
	};
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
