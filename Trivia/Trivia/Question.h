#pragma once

#include <string>
#include <vector>
#include "json.hpp"

using std::string;
using std::vector;
using nlohmann::json;

typedef unsigned int uint;

struct AnswerItem
{
	uint answerId = 0;
	string answer = "";

	AnswerItem(const uint& id, const string& answer) : answerId(id), answer(answer) { }

	bool operator ==(const AnswerItem& otherAnswerItem) const
	{
		return (answerId == otherAnswerItem.answerId) && (answer == otherAnswerItem.answer);
	}
};
void to_json(json& j, const AnswerItem& response);


class Question
{
public:
	Question();
	Question(const string& question, const vector<AnswerItem>& possibleAnswers, const uint& answerId);

	string getQuestion() const;
	vector<AnswerItem> getPossibleAnswers() const;
	uint getCorrectAnswerId() const;

	void setQuestion(const string& question);
	void setPossibleAnswers(const vector<AnswerItem>& possibleAnswers);
	void setCorrectAnswerId(const uint& answerId);


private:
	string m_question;
	vector<AnswerItem> m_possibleAnswers;
	uint m_answerId;
};
