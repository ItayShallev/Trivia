#include "Question.h"


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
	return 0;	// Always returns 0, since when a question is initialized, the correct answer is always being pushed first...
}
