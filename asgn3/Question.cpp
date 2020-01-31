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
#include <regex>
#include "Question.h"

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

Question& Question::operator=(const Question& q) {
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
    std::string answerCmp = toLower(removeSpaces(answerText));
    std::string givenCmp = toLower(removeSpaces(givenAnswer));
    return answerCmp == givenCmp;
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

std::string Question::toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c){ return std::tolower(c); });
    return str;
}

std::string Question::removeSpaces(std::string str) {
    return std::regex_replace(str, std::regex("\\s+"), std::string(""));
}
