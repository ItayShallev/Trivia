#include "Question.h"


Question::Question() : m_question(""), m_possibleAnswers(vector<string>()), m_answerId(0) { }


Question::Question(const string& question, const vector<string>& possibleAnswers, const int& answerId)
	: m_question(question), m_possibleAnswers(possibleAnswers), m_answerId(answerId) { }


string Question::getQuestion() const
{
	return this->m_question;
}


vector<string> Question::getPossibleAnswers() const
{
	return this->m_possibleAnswers;
}


int Question::getCorrectAnswerId() const
{
	return this->m_answerId;
}


void Question::setQuestion(const string& question)
{
	this->m_question = question;
}


void Question::setPossibleAnswers(const vector<string>& possibleAnswers)
{
	this->m_possibleAnswers = possibleAnswers;
}


void Question::setCorrectAnswerId(int answerId)
{
	this->m_answerId = answerId;
}
