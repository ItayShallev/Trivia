#pragma once

#include <string>
#include <map>


using std::string;
using std::map;

typedef unsigned int uint;


class Question
{
public:
	Question();
	Question(const string& question, const map<uint, string>& possibleAnswers, const uint& answerId);

	string getQuestion() const;
	map<uint, string> getPossibleAnswers() const;
	uint getCorrectAnswerId() const;

	void setQuestion(const string& question);
	void setPossibleAnswers(const map<uint, string>& possibleAnswers);
	void setCorrectAnswerId(const uint& answerId);


private:
	string m_question;
	map<uint, string> m_possibleAnswers;
	uint m_answerId;
};
