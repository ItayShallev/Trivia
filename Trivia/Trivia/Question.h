#pragma once

#include <string>
#include <vector>
#include "Structures.h"


using std::string;
using std::vector;


class Question
{
public:
	Question();
	Question(const string& question, const vector<string>& possibleAnswers, const uint& answerId);

	string getQuestion() const;
	vector<string> getPossibleAnswers() const;
	uint getCorrectAnswerId() const;

	void setQuestion(const string& question);
	void setPossibleAnswers(const vector<string>& possibleAnswers);
	void setCorrectAnswerId(uint answerId);


private:
	string m_question;
	vector<string> m_possibleAnswers;
	uint m_answerId;
};
