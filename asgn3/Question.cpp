//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-24
// Title: Assignment 2: Inheritance and Polymorphism part 1
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#include "Question.h"
#include <iostream>

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

Question::~Question() { }

Question::Question(Question& q) {
    questionText = q.questionText;
    answerText = q.answerText;
    correct = q.correct;
}

Question& Question::operator=(Question& q) {
    questionText = q.questionText;
    answerText = q.answerText;
    correct = q.correct;

    return *this;
}

Question::Question(std::vector<std::string> lineParts) {
    if (lineParts.size() != 4) {
        std::cerr << "Invalid number of short answer question parameters";
        std::cerr << std::endl;
        questionText = "";
        answerText = "";
        correct = false;
    } else {
        questionText = lineParts[2];
        answerText = lineParts[3];
        correct = false;
    }
}

void Question::showQuestion() {
    std::cout << questionText << "?" << std::endl;
}

bool Question::checkAnswer(std::string givenAnswer) {
    return answerText == givenAnswer;
}

bool Question::isCorrect() {
    return correct;
}

void Question::showAnswer() {
    std::cout << answerText << std::endl;
}

void Question::markCorrect() {
    correct = true;
}
