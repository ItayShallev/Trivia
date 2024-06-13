#include <Windows.h>
#include <random>
#include "Helper.h"

#include <iostream>


using std::shuffle;
using std::find;
using std::distance;
using std::default_random_engine;


/**
 * \brief		Turns a given string into a Buffer object
 * \param		buffer			The string to convert to Buffer object
 * \return		A Buffer object with the given string as data
 */
Buffer Helper::turnStringIntoBuffer(const string& str)
{
	return Buffer(str.begin(), str.end());
}

Buffer Helper::turnStringIntoBuffer(const char* pCh)
{
	// get the char array as string
	string charStr(pCh);

	// call the other function
	return turnStringIntoBuffer(charStr);
}

char* Helper::turnBufferToCharArr(const Buffer& buff)
{
	// get the buffer size
	size_t buffSize = buff.size();

	// init a char array
	char* retCharArr = new char[buffSize + 1];

	// iterate through the buffer elements
	for (int i = 0; i < buffSize; i++)
	{
		// add the char to the char array
		retCharArr[i] = buff[i];
	}

	// add a null terminator at the end
	retCharArr[buffSize] = '\0';

	// return the char array
	return retCharArr;
}


/**
 * \brief		Pads a given number with wantedLength - num zeros and returns the result as string
 * \param		num				The number to pad with zeros
 * \param		wantedLength	The wanted string length to return
 * \return		The given number padded with enough zeros to reach the wantedLength
 */
string Helper::padNumWith0(size_t num, uint wantedLength)
{
	// get the num string
	string numStr = std::to_string(num);

	// get the num of zeroes to add to the number
	size_t zerosToPad = wantedLength - numStr.length();

	// there are zeroes to add
	if (zerosToPad > 0)
	{
		for (int i = 0; i < zerosToPad; i++)
		{
			// add the zeros
			numStr = "0" + numStr;
		}
	}

	// return the num string
	return numStr;
}


int Helper::charToInt(const unsigned char& digit)
{
	return digit - '0';
}


RequestId Helper::convertCharsToRequestId(const unsigned char& first, const unsigned char& second)
{
	return static_cast<RequestId>((Helper::charToInt(first) * DOZEN_MULTIPLIER) + Helper::charToInt(second));
}


void Helper::setConsoleColor(unsigned int color)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

RequestResult Helper::buildRequestResult(const Buffer& buff, std::shared_ptr<IRequestHandler> handler)
{
	return {buff, handler };
}

GetRoomStateResponse Helper::buildRoomStateResponse(const RoomState& roomState)
{
	// build and return the room state response
	return {
		1,
		roomState
	};
}

int Helper::generateRandomNumber(const int& minValue, const int& maxValue)
{
    int range = maxValue - minValue + 1;
    return rand() % range + minValue;
}

set<int> Helper::generateRandomNumbersSet(const uint& setSize, const int& minValue, const int& maxValue)
{
    set<int> randomNumbers;

	// Creating a seed for randomization
	srand(static_cast<unsigned>(time(NULL)));

    while (randomNumbers.size() < setSize)
    {
        int randomNumber = Helper::generateRandomNumber(minValue, maxValue);

        // Trying to insert the random number only if it wasn't generated already
        if (randomNumbers.find(randomNumber) == randomNumbers.end())
        {
            randomNumbers.insert(randomNumber);
        }

    }

    return randomNumbers;
}

//int Helper::shuffleAnswers(vector<string>& possibleAnswers, const string correctAnswer)
//{
//	// Preparing the random engine to generate random sequence
//	std::random_device rd;
//	std::default_random_engine range(rd());
//
//	// Shuffling the possible answers vector
//	shuffle(possibleAnswers.begin(), possibleAnswers.end(), range);
//
//	// Finding the index of the correct answer
//	ptrdiff_t correctAnswerId = find(possibleAnswers.begin(), possibleAnswers.end(), correctAnswer) - possibleAnswers.begin();
//
//	return correctAnswerId;
//}
