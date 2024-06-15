#include "GameRequestHandler.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"


GameRequestHandler::GameRequestHandler(const std::shared_ptr<Game>& game, std::shared_ptr<LoggedUser>& user, GameManager& gameManager, RequestHandlerFactory* factory) : m_game(game), m_user(user), m_gameManager(gameManager), m_handlerFactory(factory)
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	uint reqId = reqInfo.id;
	return
		reqId == RequestId::LeaveGameRequestId ||
		reqId == RequestId::GetQuestionRequestId ||
		reqId == RequestId::SubmitAnswerRequestId ||
		reqId == RequestId::GetGameResultRequestId;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo reqInfo)
{
	switch (reqInfo.id)
	{
	case RequestId::LeaveGameRequestId:
		return leaveGame(reqInfo);

	case RequestId::GetQuestionRequestId:
		return getQuestion(reqInfo);

	case RequestId::SubmitAnswerRequestId:
		return submitAnswer(reqInfo);

	case RequestId::GetGameResultRequestId:
		return getGameResult(reqInfo);

	default:
		return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse()),
			std::shared_ptr<GameRequestHandler>(this, [](GameRequestHandler*) {}));
	}
}

RequestResult GameRequestHandler::getQuestion(RequestInfo reqInfo)
{
	// get the next question for the user
	Question nextQuestion = this->m_game->getQuestionForUser(this->m_user);

	uint status = nextQuestion.getQuestion() != L"NO QUESTIONS REMAINED!" ? 1 : 0;

	// build the question response
	GetQuestionResponse questionResp = {
		status,
		nextQuestion.getQuestion(),
		nextQuestion.getPossibleAnswers(),
		nextQuestion.getDifficulty()
	};

	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(questionResp), 
		std::shared_ptr<GameRequestHandler>(this, [](GameRequestHandler*) {}));
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo reqInfo)
{
	// get the answer request
	SubmitAnswerRequest answerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(reqInfo.buffer);

	// submit the request
	this->m_game->submitAnswer(this->m_user, answerRequest.answerId, answerRequest.answerTime);

	// build the submit response
	SubmitAnswerResponse submitResp = {
		1,
		this->m_game->getPlayers()[this->m_user].currentQuestion.getCorrectAnswerId()
	};

	// Checking if the game has ended
	if (this->m_game->hasGameEnded())
	{
		// Sending the game results to the DB
		this->m_gameManager.getDatabase()->submitGameStatistics(this->m_game->getPlayers());

		// Deleting the game
		this->m_gameManager.deleteGame(this->m_game->getGameId());
	}

	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(submitResp),
		std::shared_ptr<GameRequestHandler>(this, [](GameRequestHandler*) {}));
}

RequestResult GameRequestHandler::getGameResult(RequestInfo reqInfo)
{
	vector<PlayerResults> playerResults;
	map<std::shared_ptr<LoggedUser>, GameData> players = this->m_game->getPlayers();
	for (const auto& player : players)
	{
		// get the current username
		string currUsername = player.first->getUserName();

		// build the player result
		PlayerResults currPlayerResults = {
			currUsername,
			player.second.correctAnswerCount,
			player.second.wrongAnswerCount,
			player.second.averageAnswerTime
		};

		// add the result to the vector
		playerResults.push_back(currPlayerResults);

	}

	// build the game results response
	GetGameResultResponse gameResultResp = { 1, playerResults };



	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(gameResultResp),
		std::shared_ptr<GameRequestHandler>(this, [](GameRequestHandler*) {}));
}


RequestResult GameRequestHandler::leaveGame(RequestInfo reqInfo)
{
	// remove the user from the game
	this->m_game->removeUser(this->m_user);

	// create a new menu request handler	
	std::shared_ptr<MenuRequestHandler> newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_user);

	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse()), newHandler);
}
