#pragma once

#include "Structures.h"


class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer buff);
	static SignupRequest deserializeSignupRequest(Buffer buff);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(Buffer buff);
	static JoinRoomRequest deserializeJoinRoomRequest(Buffer buff);
	static CreateRoomRequest deserializeCreateRoomRequest(Buffer buff);
	static CheckIfUserExistsRequest deserializeCheckIfUserExistsRequest(Buffer buff);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(Buffer buff);

private:
	static string getMessageFromBuffer(Buffer buff);
};
