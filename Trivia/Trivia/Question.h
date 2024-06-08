#pragma once

#include <string>
#include <vector>


using std::string;
using std::vector;


class Question
{
public:
	Question();
	Question(const string& question, const vector<string>& possibleAnswers, const int& answerId);

	string getQuestion() const;
	vector<string> getPossibleAnswers() const;
	int getCorrectAnswerId() const;

	void setQuestion(const string& question);
	void setPossibleAnswers(const vector<string>& possibleAnswers);
	void setCorrectAnswerId(int answerId);


private:
	string m_question;
	vector<string> m_possibleAnswers;
	int m_answerId;
};
