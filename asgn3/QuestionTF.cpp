#include <iostream>
#include <string>
#include <cctype>
#include "Question.h"
#include "QuestionTF.h"

QuestionTF::QuestionTF() {
    std::string questionText;
    std::string answerText;
    correct = false;
}

QuestionTF::QuestionTF(std::string question, std::string answer) {
    questionText = question;
    answerText = answer;
    correct = false;
}

void QuestionTF::showQuestion() {
    std::cout << questionText << std::endl;
    return;
}

void QuestionTF::showAnswer() {
    std::cout << answerText << std::endl;
    return;
}

bool QuestionTF::checkAnswer(std::string answer) {
    char c = std::tolower(answer.c_str()[0]);
    char a = std::tolower(answerText.c_str()[0]);

    return c == a;
}
