#include "Question.h"


Question::Question(const string& question, const vector<string>& possibleAnswers, const uint& answerId)
	: m_question(question), m_possibleAnswers(possibleAnswers), m_answerId(answerId) { }


string Question::getQuestion() const
{
	return this->m_question;
}


vector<string> Question::getPossibleAnswers() const
{
	return this->m_possibleAnswers;
}


uint Question::getCorrectAnswerId() const
{
	return this->m_answerId;
}
