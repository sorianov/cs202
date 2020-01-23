#include "Question.h"
#include <iostream>
#include <cctype>

Question::Question() {
    std::string questionText;
    std::string answerText;
    correct = false;
}

Question::Question(std::string question, std::string answer) {
    questionText = question;
    answerText = answer;
    correct = false;
}

void Question::showQuestion() {
    std::cout << questionText << std::endl;
    return;
}

bool Question::checkAnswer(std::string givenAnswer) {
    if (answerText == givenAnswer) {
        return true;
    }
    return false;
}

bool Question::isCorrect() {
    return correct;
}

void Question::showAnswer() {
    std::cout << answerText << std::endl;
    return;
}

void Question::markCorrect() {
    correct = true;
    return;
}

std::string toLower(std::string source) {
    std::string dest;
    dest.resize(source.size());
    for (unsigned int i = 0; i < source.size(); ++i) {
        dest[i] = std::tolower(source[i]);
    }
    return dest;
}
