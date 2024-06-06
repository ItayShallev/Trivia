#include <memory>
#include  "Server.h"
#include "SqliteDatabase.h"


int main()
{
	// Creating a database instance
	std::unique_ptr<IDatabase> db = std::make_unique<SqliteDatabase>("database.db");

	// Creating a factory that will be responsible for managing the handling of incoming requests
	RequestHandlerFactory factory(db.get());

	// Creating a server instance
	Server server(db.get(), &factory);
	server.run();		// Starting the server

	return 0;
}
