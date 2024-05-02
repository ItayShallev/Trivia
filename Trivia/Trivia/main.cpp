#include  "Server.h"
#include "SqliteDatabase.h"

int main()
{
	IDatabase* db = new SqliteDatabase("database.db");
	RequestHandlerFactory factory(db);
	Server server(db, &factory);
	server.run();

	return 0;
}
