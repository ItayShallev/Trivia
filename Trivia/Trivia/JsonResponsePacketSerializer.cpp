#include "JsonResponsePacketSerializer.h"
#include "json.hpp"


using std::to_string;
using json = nlohmann::json;



/**
 * \brief		Serializes an error response
 * \param		errorResponse		The ErrorResponse object to serializer
 * \return		A buffer containing the errorResponse in the protocol's format
 */
Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
	json j;

	// Creating the json object to insert in the data section
	j["message"] = errorResponse.message;
	string jsonString = j.dump();

	// Adding the protocol's remaining metadata to the response
	string response = std::to_string(ErrorResponseId);
	response += padNumWith0(jsonString.length());
	response += jsonString;

	return JsonResponsePacketSerializer::turnStringIntoBuffer(response);
}


/**
 * \brief		Serializes a login response
 * \param		loginResponse		The LoginResponse object to serializer
 * \return		A buffer containing the loginResponse in the protocol's format
 */
Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	json j;

	// Creating the json object to insert in the data section
	j["status"] = loginResponse.status;
	string jsonString = j.dump();

	// Adding the protocol's remaining metadata to the response
	string response = std::to_string(LoginResponseId);
	response += padNumWith0(jsonString.length());
	response += jsonString;

	return JsonResponsePacketSerializer::turnStringIntoBuffer(response);
}


/**
 * \brief		Serializes an signup response
 * \param		signupResponse		The SignupResponse object to serializer
 * \return		A buffer containing the signupResponse in the protocol's format
 */
Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	json j;

	// Creating the json object to insert in the data section
	j["status"] = signupResponse.status;
	string jsonString = j.dump();

	// Adding the protocol's remaining metadata to the response
	string response = std::to_string(SignupResponseId);
	response += padNumWith0(jsonString.length());
	response += jsonString;

	return JsonResponsePacketSerializer::turnStringIntoBuffer(response);
}



/**
 * \brief		Turns a given string into a Buffer object
 * \param		buffer			The string to convert to Buffer object
 * \return		A Buffer object with the given string as data
 */
Buffer JsonResponsePacketSerializer::turnStringIntoBuffer(string& buffer)
{
	return Buffer(buffer.begin(), buffer.end());
}


/**
 * \brief		Pads a given number with wantedLength - num zeros and returns the result as string
 * \param		num				The number to pad with zeros
 * \param		wantedLength	The wanted string length to return
 * \return		The given number padded with enough zeros to reach the wantedLength
 */
string JsonResponsePacketSerializer::padNumWith0(int num, int wantedLength)
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
