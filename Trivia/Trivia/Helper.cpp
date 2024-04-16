#include "Helper.h"


/**
 * \brief		Turns a given string into a Buffer object
 * \param		buffer			The string to convert to Buffer object
 * \return		A Buffer object with the given string as data
 */
Buffer Helper::turnStringIntoBuffer(const string& str)
{
	return Buffer(str.begin(), str.end());
}


/**
 * \brief		Pads a given number with wantedLength - num zeros and returns the result as string
 * \param		num				The number to pad with zeros
 * \param		wantedLength	The wanted string length to return
 * \return		The given number padded with enough zeros to reach the wantedLength
 */
string Helper::padNumWith0(int num, int wantedLength)
{
	// get the num string
	string numStr = std::to_string(num);

	// get the num of zeroes to add to the number
	int zerosToPad = wantedLength - numStr.length();

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
