import sys
import requests
import time
import json
import html
import sqlite3
from colorama import Fore, Back, Style, init

TIMES_TO_REQUEST_CL_ARG_INDEX = 1
TRIVIA_API_COOLDOWN = 5

NUMBER_OF_QUESTIONS_TO_FETCH = 50       # This is the max amount of questions
QUESTIONS_URL = "https://opentdb.com/api.php?amount=" + str(NUMBER_OF_QUESTIONS_TO_FETCH) + "&type=multiple"
SUCCESS_CODE = 0


def insert_questions_to_db(questions: json) -> None:
    """
    Inserts the questions inside the given json object into the database
    :param questions: The json object containing the questions
    :return: None
    :rtype: None
    """
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()

    for question in questions["results"]:
        # Constructing the record with html escape sequences translated to readable characters
        record = [html.unescape(q) for q in [question["type"], question["difficulty"], question["category"],
                                         question["question"], question["correct_answer"],
                                         question["incorrect_answers"][0], question["incorrect_answers"][1],
                                         question["incorrect_answers"][2]]]

        # Executing the insert statement into the QUESTIONS table
        cursor.execute("""INSERT INTO QUESTIONS
        (TYPE, DIFFICULTY, CATEGORY, QUESTION,
        CORRECT_ANSWER, INCORRECT_ANSWER_1,
        INCORRECT_ANSWER_2, INCORRECT_ANSWER_3)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?)
        """, record)

    conn.commit()       # Commiting the changes that have been made


def main():
    init()      # For colorful printing

    print(Fore.YELLOW + "Sending " + sys.argv[TIMES_TO_REQUEST_CL_ARG_INDEX] + " Requests" + Fore.WHITE)

    for i in range(int(sys.argv[TIMES_TO_REQUEST_CL_ARG_INDEX])):
        if i != 0:          # Waiting between each request
            time.sleep(TRIVIA_API_COOLDOWN)

        questions = requests.get(QUESTIONS_URL)
        print(Fore.YELLOW + "RETURN CODE: " + str(questions.json()["response_code"]) + Fore.WHITE)

        if questions.json()["response_code"] == SUCCESS_CODE:
            insert_questions_to_db(questions.json())
        else:
            print(Fore.YELLOW + "OpenTrivia error (Code: " + str(questions.json()["response_code"]) + ")" + Fore.WHITE)

    print(Fore.YELLOW + "Finished fetching questions..." + Fore.YELLOW)


if __name__ == '__main__':
    main()
