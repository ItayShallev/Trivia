#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include <iostream>
#include "WSAInitializer.h"


Server::Server(IDatabase* database, RequestHandlerFactory* factory) : m_database(database), m_handlerFactory(*factory), m_communicator(&m_handlerFactory)
{
}

void Server::run()
{
	try
	{
		WSAInitializer wsaInit;
		this->m_communicator.startHandleRequests();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << '\n';
	}
}
