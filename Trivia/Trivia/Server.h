#pragma once

#include <WinSock2.h>
#include <string>

using namespace std;

class Server
{
public:
	Server();
	~Server();


	void start(int port);

	

private:
	
	SOCKET m_serverSocket;

	
	void acceptClient(SOCKET serverSocket);

	// handlers
	void clientHandler(SOCKET clientSocket);
	void connectorHandler(); 

	string receiveData(SOCKET soc);
	void sendData(SOCKET soc, string message);
};
