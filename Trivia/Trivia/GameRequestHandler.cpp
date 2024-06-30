#include "GameRequestHandler.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"


using std::sort;


GameRequestHandler::GameRequestHandler(const shared_ptr<Game>& game, shared_ptr<LoggedUser>& user, GameManager& gameManager, RequestHandlerFactory* factory)
	: m_game(game), m_user(user), m_gameManager(gameManager), m_handlerFactory(factory) { }


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
			shared_ptr<GameRequestHandler>(this, [](GameRequestHandler*) {}));
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
		shared_ptr<GameRequestHandler>(this, [](GameRequestHandler*) {}));
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
		shared_ptr<GameRequestHandler>(this, [](GameRequestHandler*) {}));
}


RequestResult GameRequestHandler::getGameResult(RequestInfo reqInfo)
{
	vector<PlayerResults> playerResults;
	map<shared_ptr<LoggedUser>, GameData> players = this->m_game->getPlayers();

	for (const auto& player : players)
	{
		// get the current username
		string currUsername = player.first->getUserName();

		// build the player result
		PlayerResults currPlayerResults = {
			currUsername,
			player.second.correctAnswerCount,
			player.second.wrongAnswerCount,
			player.second.averageAnswerTime,
			player.second.points,
			0						// Will be assigned later...
		};

		// add the result to the vector
		playerResults.push_back(currPlayerResults);
	}

	// Sorting the players by number of points
	sort(playerResults.begin(), playerResults.end(),
		[](const PlayerResults& playerResults, const PlayerResults& otherPlayerResults)
		{
			if (playerResults.points == otherPlayerResults.points)
			{
				return playerResults.averageAnswerTime < otherPlayerResults.averageAnswerTime;
			}
			return playerResults.points > otherPlayerResults.points;
		});

	// Assigning ranks based on the vector's order
	for (int i = 0; i < playerResults.size(); ++i)
	{
		playerResults[i].rank = i + 1;
	}

	// build the game results response
	GetGameResultResponse gameResultResp = { 1, playerResults };

	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(gameResultResp),
		shared_ptr<GameRequestHandler>(this, [](GameRequestHandler*) {}));
}


RequestResult GameRequestHandler::leaveGame(RequestInfo reqInfo)
{
	Room& gameRoom = this->m_handlerFactory->getRoomManager().getRoom(this->m_game->getGameId());		// Room and game in a room have the same id

	// Resetting the room status to let users in the menu see the room (only if the admin hasn't closed it)
	if (gameRoom.getRoomStatus() != RoomStatus::Closed)
	{
		if (gameRoom.getUsers().size() < gameRoom.getRoomData().maxPlayers)
		{
			gameRoom.setRoomStatus(RoomStatus::Waiting);
		}
		else
		{
			gameRoom.setRoomStatus(RoomStatus::Full);
		}
	}

	shared_ptr<IRequestHandler> newHandler = nullptr;

	// Checking if the user is an admin or a member of the room
	if (this->m_user->getUserName() == gameRoom.getAdmin())		// If the user is the admin of the room
	{
		newHandler = this->m_handlerFactory->createRoomAdminRequestHandler(this->m_user, gameRoom);
	}
	else			// User is a room member
	{
		newHandler = this->m_handlerFactory->createRoomMemberRequestHandler(this->m_user, gameRoom);
	}

	// Incrementing the number of users who finished the game if the user left mid-game
	if (this->m_user->getUserStatus() == UserStatus::InGame)
	{
		this->m_game->incrementNumFinished();

		map<shared_ptr<LoggedUser>, GameData>& players = this->m_game->getPlayers();
		players[this->m_user].leftGame = true;
	}

	// Checking if the game needs to be deleted (if everyone left the game)
	if (!this->m_game->isAnyPlayerActive())
	{
		this->m_gameManager.deleteGame(this->m_game->getGameId());
	}

	// Changing the user's status
	this->m_user->setUserStatus(UserStatus::InWaitingRoom);

	// build and return the request result
	return Helper::buildRequestResult(JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse()), newHandler);
}
