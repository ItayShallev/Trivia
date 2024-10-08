#include "Communicator.h"
#include <exception>
#include <iostream>
#include <thread>
#include "Constants.h"
#include "Helper.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h"


using std::exception;
using std::cout;
using std::thread;
using std::to_string;
using std::make_pair;


Communicator::Communicator(RequestHandlerFactory* handlerFactory) : m_serverSocket(INVALID_SOCKET), m_handlerFactory(*handlerFactory) { }


void Communicator::startHandleRequests()
{
	initSocket();
	
	// run the bind and listen thread
	thread connectorThread(&Communicator::bindAndListen, this);
	connectorThread.join(); // join the thread
}


void Communicator::bindAndListen()
{
	// bind
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(SERVER_PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw exception(__FUNCTION__ " - listen");

	// wait for clients
	thread waitForClientsThread(&Communicator::waitForClients, this);
	waitForClientsThread.join(); // join the thread
}


void Communicator::handleNewClient(SOCKET clientSoc, int id)
{
	try
	{
		while (true)
		{
			// status
 			cout << '\n' << "waiting for message ..." << '\n';

			// get the data message
			Buffer buff = receiveDataFromSocket(clientSoc);
			if (buff.size() == 0) // might imply the user quit
			{
				cout << "client quit, closing socket" << '\n';
				throw exception("client quit");
			}

			// Printing the request of the client
			Helper::setConsoleColor(CYAN);
			cout << "CLIENT " << id << ":\n";
			for (size_t i = 0; i < buff.size(); i++)
			{
				cout << buff[i];
			}
			cout << "\n";
			Helper::setConsoleColor(WHITE);

			// get the current time
            time_t now = time(nullptr);

			// build a request info
			RequestInfo reqInfo = { buff, Helper::convertCharsToRequestId(buff[0], buff[1]),now};

			// get the client request handler 
			IRequestHandler* clientRequestHandler = m_clients[clientSoc].get();

			// check whether the request is relevant
			bool isReqRelevant = clientRequestHandler->isRequestRelevant(reqInfo);
			if (!isReqRelevant)
			{
				// send that client an error response
				ErrorResponse errorResp;
				sendDataToSocket(clientSoc, JsonResponsePacketSerializer::serializeResponse(errorResp));
			}

			// get the request result
			RequestResult reqResult = clientRequestHandler->handleRequest(reqInfo);

			// Checking if the handler has been changed
			if (m_clients[clientSoc] != reqResult.newHandler)
			{
				// Resetting the old handler (Calls the handler's destructor)
				m_clients[clientSoc].reset();

				// Assigning the client the new handler
				m_clients[clientSoc] = shared_ptr<IRequestHandler>(reqResult.newHandler);
			}

			// Printing the server's response
			Helper::setConsoleColor(GREEN);
			for(size_t i = 0; i < reqResult.response.size(); i++)
			{
				cout << reqResult.response[i];
			}
			Helper::setConsoleColor(WHITE);

			// send the response to the client
			sendDataToSocket(clientSoc, reqResult.response);
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << 'n';
		closesocket(clientSoc);
	}
}


void Communicator::initSocket()
{
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
		throw exception(__FUNCTION__ " - socket");
}


void Communicator::waitForClients()
{
	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		cout << "Waiting for client connection request\n";
		acceptClient(this->m_serverSocket);
	}
}


void Communicator::acceptClient(SOCKET serverSoc)
{
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET clientSoc = accept(serverSoc, NULL, NULL);
	if (clientSoc == INVALID_SOCKET)
		throw exception(__FUNCTION__);

	// we got a client, print status
	cout << "Client accepted. Server and client can speak\n";

	// Creating a shared pointer to a LoginRequestHandler
	shared_ptr<IRequestHandler> newLoginRequestHandler = this->m_handlerFactory.createLoginRequestHandler();
	auto newClientInfo = make_pair(clientSoc, newLoginRequestHandler);

	// adding the <Socket,Handler> pair to the clients map
	this->m_clients.insert(newClientInfo);

	// open a thread for the new client
	thread clientThread(&Communicator::handleNewClient, this, clientSoc, this->m_clients.size());
	clientThread.detach();		// detach the thread
}


Buffer Communicator::receiveDataFromSocket(SOCKET clientSoc)
{
	// init data var
	char* data = new char[DEFAULT_BUFFER_SIZE];

	// receive data from the socket
	const int res = recv(clientSoc, data, DEFAULT_BUFFER_SIZE - 1, 0);

	// failed
	if (res == INVALID_SOCKET)
	{
		// throw exception
		string s = "Error while receiving from socket: ";
		s += to_string(clientSoc);
		throw exception(s.c_str());
	}

	// add a null terminator
	data[res] = '\0';

	// convert the received data into a string
	Buffer receivedData = Helper::turnStringIntoBuffer(data);

	// delete the initialized data variable
	delete[] data;


	// return the data received
	return receivedData;
}


void Communicator::sendDataToSocket(SOCKET clientSoc, Buffer data)
{
	// convert the Buffer object into sendable data (dynamically allocated memory)
	char* sendableData = Helper::turnBufferToCharArr(data);

	// send the data 
	if (send(clientSoc, sendableData, data.size(), 0) == INVALID_SOCKET)
	{
		delete[] sendableData;
		throw exception("Error while sending message to client");		// throwing an exception if failed
	}

	delete[] sendableData;
}
