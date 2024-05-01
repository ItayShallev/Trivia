#pragma once


#include "LoginManager.h"
#include "LoginRequestHandler.h"
class LoginRequestHandler;
#include "MenuRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManger;
	IDatabase* m_database;

public:
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();
};

