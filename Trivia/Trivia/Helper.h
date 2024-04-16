#pragma once

#include "Structures.h"
#include "Constants.h"


class Helper
{
public:
	static Buffer turnStringIntoBuffer(const string& str);

	static string padNumWith0(int num, int wantedLength = DATA_BYTE_LENGTH);
};
