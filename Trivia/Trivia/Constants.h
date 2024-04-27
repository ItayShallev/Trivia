#pragma once

// ************************** SERVER CONSTANTS *************************
#define SERVER_PORT 8888
#define DEFAULT_BUFFER_SIZE 255			// TODO: remove when message format is established, update receive data




// ************************** ENUMS *************************
enum RequestId
{
	LoginRequestId = 0,
	SignupRequestId = 1
};


enum ResponseId
{
	LoginResponseId = 0,
	SignupResponseId = 1,
	ErrorResponseId = 2
};




// ************************** DE/SERIALIZERS *************************
#define DATA_BYTE_LENGTH 4
