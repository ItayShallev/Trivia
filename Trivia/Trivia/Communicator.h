#pragma once

#include  "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <WinSock2.h>
#include <map>
#include <string>


using std::map;
using std::string;
using std::shared_ptr;


class Communicator
{
public:
	Communicator(RequestHandlerFactory* handlerFactory);
	void startHandleRequests();

private:
	// members
	SOCKET m_serverSocket;
	map<SOCKET, shared_ptr<IRequestHandler>> m_clients;
	RequestHandlerFactory m_handlerFactory;	

	// methods
	void bindAndListen();
	void handleNewClient(SOCKET clientSoc, int id);

	void initSocket();
	void waitForClients();
	void acceptClient(SOCKET serverSoc);
	static Buffer receiveDataFromSocket(SOCKET clientSoc);
	static void sendDataToSocket(SOCKET clientSoc, Buffer data);
};
