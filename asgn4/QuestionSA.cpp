//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-29
// Title: Assignment 2: Inheritance and Polymorphism part 2
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
// needs extra compiler options
//#include <regex>
#include "QuestionSA.h"

QuestionSA::QuestionSA() {
    std::string questionText;
    std::string answerText;
    correct = false;
}

QuestionSA::QuestionSA(std::string question, std::string answer) {
    questionText = question;
    answerText = answer;
    correct = false;
}

QuestionSA::~QuestionSA() { }

QuestionSA::QuestionSA(QuestionSA& q) { questionText = q.questionText;
    answerText = q.answerText;
    correct = q.correct;
}

QuestionSA& QuestionSA::operator=(const QuestionSA& q) {
    questionText = q.questionText;
    answerText = q.answerText;
    correct = q.correct;

    return *this;
}

QuestionSA::QuestionSA(std::vector<std::string> lineParts) {
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

void QuestionSA::showQuestion() {
    std::cout << questionText << "?" << std::endl;
}

bool QuestionSA::checkAnswer(std::string givenAnswer) {
    /* Doesn't work on school g++ without extra compiler options
    std::string answerCmp = toLower(removeSpaces(answerText));
    std::string givenCmp = toLower(removeSpaces(givenAnswer));
    */
    std::string answerCmp = toLower(answerText);
    std::string givenCmp = toLower(givenAnswer);
    return answerCmp == givenCmp;
}

bool QuestionSA::isCorrect() {
    return correct;
}

void QuestionSA::showAnswer() {
    std::cout << answerText << std::endl;
}

void QuestionSA::markCorrect() {
    correct = true;
}

unsigned char QuestionSA::lower(unsigned char c) {
    return std::tolower(c);
}

std::string QuestionSA::toLower(std::string str) {
    /* Doesn't work on school g++ without extra compiler options
    std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c){ return std::tolower(c); });
            */
    std::transform(str.begin(), str.end(), str.begin(), QuestionSA::lower);

    return str;
}

/* Doesn't work on school g++ without extra compiler options
std::string QuestionSA::removeSpaces(std::string str) {
    return std::regex_replace(str, std::regex("\\s+"), std::string(""));
}*/
