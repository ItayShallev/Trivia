#pragma once

#include  "IRequestHandler.h"
#include <WinSock2.h>
#include <map>
#include <string>

using std::map;
using std::string;


class Communicator
{
public:
	void startHandleRequests();

private:
	// members
	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;

	// methods
	void bindAndListen();
	void handleNewClient(SOCKET clientSoc);

	void initSocket();
	void waitForClients();
	void acceptClient(SOCKET serverSoc);
	static Buffer receiveDataFromSocket(SOCKET clientSoc);
	static void sendDataToSocket(SOCKET clientSoc, Buffer data);
};

