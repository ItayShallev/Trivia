#pragma once

#include <string>
#include <vector>
#include "Constants.h"
#include "json.hpp"


using std::string;
using std::wstring;
using std::vector;
using nlohmann::json;


typedef unsigned int uint;


struct AnswerItem
{
	uint answerId = 0;
	wstring answer;

	AnswerItem(const uint& id, const wstring& answer) : answerId(id), answer(answer) { }

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
	Question(const wstring& question, const vector<AnswerItem>& possibleAnswers, const uint& answerId, const QuestionDifficulty& questionDifficulty);

	wstring getQuestion() const;
	vector<AnswerItem> getPossibleAnswers() const;
	uint getCorrectAnswerId() const;
	QuestionDifficulty getDifficulty() const;

	void setQuestion(const wstring& question);
	void setPossibleAnswers(const vector<AnswerItem>& possibleAnswers);
	void setCorrectAnswerId(const uint& answerId);
	void setDifficulty(const QuestionDifficulty& difficulty);

	static QuestionDifficulty getDifficultyFromString(const string& stringDifficulty);

private:
	wstring m_question;
	vector<AnswerItem> m_possibleAnswers;
	uint m_answerId;
	QuestionDifficulty m_difficulty;
};
