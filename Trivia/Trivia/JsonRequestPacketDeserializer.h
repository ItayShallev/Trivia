#pragma once
#include "Tools.h"
#include "Requests.h"


class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer buff);
	static SignupRequest deserializeSignupRequest(Buffer buff);

private:
	static string getMessageFromBuffer(Buffer buff);

};

