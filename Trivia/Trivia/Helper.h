#pragma once

#include <set>
#include "GameStructures.h"
#include "ResponseStructures.h"
#include "Constants.h"

using std::string;
using std::set;
using std::shared_ptr;


class Helper
{
public:
	static Buffer turnStringIntoBuffer(const string& str);
	static Buffer turnStringIntoBuffer(const char* pCh);
	static char* turnBufferToCharArr(const Buffer& buff);

	static string padNumWith0(size_t num, uint wantedLength = DATA_BYTE_LENGTH);
	static int charToInt(const unsigned char& digit);
	static RequestId convertCharsToRequestId(const unsigned char& first, const unsigned char& second);
	static void setConsoleColor(unsigned int color);

	static RequestResult buildRequestResult(const Buffer& buff, shared_ptr<IRequestHandler> handler);
	static GetRoomStateResponse buildRoomStateResponse(const RoomState& roomState);

	static int generateRandomNumber(const int& minValue, const int& maxValue);
	static set<int> generateRandomNumbersSet(const uint& setSize, const int& minValue, const int& maxValue);

	static double getPointsPossibleForDifficulty(const QuestionDifficulty& questionDifficulty);
};
