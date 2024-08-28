#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include <iostream>
#include "WSAInitializer.h"


using std::exception;
using std::cout;


Server::Server(IDatabase* database, RequestHandlerFactory* factory) : m_database(database), m_handlerFactory(*factory), m_communicator(&m_handlerFactory) { }


void Server::run()
{
	try
	{
		WSAInitializer wsaInit;
		this->m_communicator.startHandleRequests();
	}
	catch (exception& e)
	{
		cout << "Error occured: " << e.what() << '\n';
	}
}
