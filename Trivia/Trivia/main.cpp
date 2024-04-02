#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include  "Server.h"
#include "WSAInitializer.h"


#define SERVER_PORT 8888

int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		myServer.start(SERVER_PORT);
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}


	return 0;
}