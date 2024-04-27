#pragma once

#include "Structures.h"
#include "Constants.h"


class Helper
{
public:
	static Buffer turnStringIntoBuffer(const string& str);
	static Buffer turnStringIntoBuffer(const char* pCh);
	static char* turnBufferToCharArr(const Buffer& buff);

	static string padNumWith0(int num, int wantedLength = DATA_BYTE_LENGTH);
	static int charToInt(const char& digit);
};
