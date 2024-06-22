#include "Question.h"


Question::Question() : m_question(L""), m_possibleAnswers(vector<AnswerItem>()), m_answerId(0), m_difficulty(QuestionDifficulty::Easy) { }


Question::Question(const wstring& question, const vector<AnswerItem>& possibleAnswers, const uint& answerId, const QuestionDifficulty& questionDifficulty)
	: m_question(question), m_possibleAnswers(possibleAnswers), m_answerId(answerId), m_difficulty(questionDifficulty) { }


wstring Question::getQuestion() const
{
	return this->m_question;
}


vector<AnswerItem> Question::getPossibleAnswers() const
{
	return this->m_possibleAnswers;
}


uint Question::getCorrectAnswerId() const
{
	return this->m_answerId;
}


QuestionDifficulty Question::getDifficulty() const
{
	return this->m_difficulty;
}


void Question::setQuestion(const wstring& question)
{
	this->m_question = question;
}


void Question::setPossibleAnswers(const vector<AnswerItem>& possibleAnswers)
{
	this->m_possibleAnswers = possibleAnswers;
}


void Question::setCorrectAnswerId(const uint& answerId)
{
	this->m_answerId = answerId;
}


void Question::setDifficulty(const QuestionDifficulty& difficulty)
{
	this->m_difficulty = difficulty;
}


QuestionDifficulty Question::getDifficultyFromString(const string& stringDifficulty)
{
	if (stringDifficulty == "easy")
	{
		return QuestionDifficulty::Easy;
	}
	else if (stringDifficulty == "medium")
	{
		return QuestionDifficulty::Medium;
	}
	else
	{
		return QuestionDifficulty::Hard;
	}
}
