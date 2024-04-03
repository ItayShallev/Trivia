#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include <iostream>
#include "WSAInitializer.h"


void Server::run()
{
	try
	{
		WSAInitializer wsaInit;
		this->m_communicator.startHandleRequests();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
}
