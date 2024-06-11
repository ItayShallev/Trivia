#include "Question.h"


Question::Question() : m_question(""), m_possibleAnswers(vector<AnswerItem>()), m_answerId(0) { }


Question::Question(const string& question, const vector<AnswerItem>& possibleAnswers, const uint& answerId)
	: m_question(question), m_possibleAnswers(possibleAnswers), m_answerId(answerId) { }


string Question::getQuestion() const
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


void Question::setQuestion(const string& question)
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
