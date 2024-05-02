#pragma once

#include "Communicator.h"


class Server
{
public:
	Server(IDatabase* database, RequestHandlerFactory* factory);
	void run();

private:
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;
};
