#pragma once

#include  "IRequestHandler.h"
#include <WinSock2.h>
#include <map>
#include <string>

#include "RequestHandlerFactory.h"

using std::map;
using std::string;


class Communicator
{
public:
	void startHandleRequests();
	Communicator(RequestHandlerFactory* handlerFactory);

private:
	// members
	SOCKET m_serverSocket;
	map<SOCKET, std::shared_ptr<IRequestHandler>> m_clients;
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

