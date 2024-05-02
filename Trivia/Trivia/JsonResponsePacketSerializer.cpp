#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include "Helper.h"


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
	response += Helper::padNumWith0(jsonString.length());
	response += jsonString;

	return Helper::turnStringIntoBuffer(response);
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
	response += Helper::padNumWith0(jsonString.length());
	response += jsonString;

	return Helper::turnStringIntoBuffer(response);
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
	response += Helper::padNumWith0(jsonString.length());
	response += jsonString;

	return Helper::turnStringIntoBuffer(response);
}
