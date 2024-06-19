#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"


class RequestHandlerFactory;


class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(const std::shared_ptr<Game>& game, std::shared_ptr<LoggedUser>& user, GameManager& gameManager, RequestHandlerFactory* factory);
	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	std::shared_ptr<Game> m_game;
	std::shared_ptr<LoggedUser> m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult getQuestion(RequestInfo reqInfo);
	RequestResult submitAnswer(RequestInfo reqInfo);
	RequestResult getGameResult(RequestInfo reqInfo);
	RequestResult leaveGame(RequestInfo reqInfo);
};
