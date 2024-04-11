#pragma once

#include <map>
#include "Tools.h"
#include "Responses.h"

using std::to_string;
using std::map;


class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	static Buffer serializeResponse(const LoginResponse& loginResponse);
	static Buffer serializeResponse(const SignupResponse& signupResponse);

private:
	static Buffer turnStringIntoBuffer(string& buffer);
	static string padNumWith0(int num, int wantedLength = 4);
};
