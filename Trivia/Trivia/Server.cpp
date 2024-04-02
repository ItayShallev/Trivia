#include "Server.h"
#include <exception>
#include <iostream>
#include <fstream>
#include <thread>

#define DEFAULT_BUFFER_SIZE 255

Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
		throw exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(this->m_serverSocket);
	}
	catch (...) {}
}

void Server::start(int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw exception(__FUNCTION__ " - listen");

	// print status
	cout << "Listening on port " << port << endl;

	// run the connector thread
	thread connectorThread(&Server::connectorHandler, this);
	connectorThread.join(); // join the connector thread
}

void Server::connectorHandler()
{
	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		cout << "Waiting for client connection request" << endl;
		acceptClient(this->m_serverSocket);
	}
}

void Server::acceptClient(SOCKET serverSocket)
{

	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw exception(__FUNCTION__);

	cout << "Client accepted. Server and client can speak" << endl;
	
	
	// the function that handle the conversation with the client
	thread clientThread(&Server::clientHandler, this, client_socket);
	clientThread.detach(); // detach the thread
}


void Server::clientHandler(SOCKET clientSocket)
{
	try
	{
		while (true)
		{

			// status
			cout << "waiting for message ..." << endl;

			// get the data message
			string msg = receiveData(clientSocket);

			// print the message
			cout << "got message: " << msg << endl;

			// send a test message
			string resp = "test";
			cout << "sending test message: '" << resp << "'" << endl;
			sendData(clientSocket, resp);
		}
	}
	catch (const exception& e)
	{
		closesocket(clientSocket);
	}


}



string Server::receiveData(SOCKET soc)
{
	// init data var
	char* data = new char[DEFAULT_BUFFER_SIZE];

	// recieve data from the socket
	const int res = recv(soc, data, DEFAULT_BUFFER_SIZE - 1, 0);

	// failed
	if (res == INVALID_SOCKET)
	{
		// throw exception
		string s = "Error while receiving from socket: ";
		s += to_string(soc);
		throw exception(s.c_str());
	}

	// return the data received
	return string(data);
}

void Server::sendData(SOCKET sc, string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw exception("Error while sending message to client");
	}
}
