#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;


class Question
{
public:
	string getQuestion() const;
	vector<string> getPossibleAnswers() const;
	int getCorrectAnswerId() const;


private:
	string m_question;
	vector<string> m_possibleAnswers;
};
