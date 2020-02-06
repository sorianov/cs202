//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-29
// Title: Assignment 2: Inheritance and Polymorphism part 2
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
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

QuestionTF::QuestionTF(std::vector<std::string> lineParts) {
    if (lineParts.size() != 4) {
        std::cerr << "Invalid number of true/false question parameters";
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

QuestionTF::QuestionTF(const QuestionTF& q) {
    questionText = q.questionText;
    answerText = q.answerText;
    correct = q.correct;
}

QuestionTF& QuestionTF::operator=(const QuestionTF& q) {
    questionText = q.questionText;
    answerText = q.answerText;
    correct = q.correct;

    return *this;
}

QuestionTF::~QuestionTF() { }

void QuestionTF::showQuestion() {
    std::cout << questionText << ". (True or False?)";
    std::cout << std::endl;
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
