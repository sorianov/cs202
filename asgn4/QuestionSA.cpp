//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-02-09
// Title: Assignment 3: Abstract classes, exceptions, and other error handling
// Description: Create a basic and robust quiz application that can extended
// via inheritance in the future.
//----------------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <sstream>
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
    validateQuestionLineParts(lineParts);
    /*
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
    */
    questionText = lineParts[2];
    answerText = lineParts[3];
    correct = false;
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

// TODO Make custom exceptions for less repetitive code.
bool QuestionSA::validateQuestionLineParts(std::vector<std::string> parts) {
    std::stringstream ss;
    std::string tmp;
    // Make sure we have a correct vector size before we start accessing
    // out of bound members.
    if (parts.size() > 4) {
        ss << "Invalid number of short answer question parameters. There are ";
        ss << "too many fields separated by '|' characters. ";
        ss << "Expected format:\n";
        ss << "\tS|level|question|answer";
        throw(ss.str());
    }
    if (parts.size() < 4) {
        ss << "Invalid number of short answer question parameters. There are ";
        ss << "too few fields separated by '|' characters. ";
        ss << "Expected format:\n";
        ss << "\tS|level|question|answer";
        throw(ss.str());
    }
    // Validate Question code
    tmp = parts.at(0);
    if (tmp.size() != 1) {
        // Too many characters in field
        ss << "Invalid short answer question code " << tmp << ". ";
        ss << "Expected S.";
        throw(ss.str());
    }
    if (std::tolower(tmp.at(0)) != 's') {
        // Wrong code
        ss << "Invalid short answer question code " << tmp << ". ";
        ss << "Expected S.";
        throw(ss.str());
    }
    // Validate Level
    tmp = parts.at(1);
    if (tmp.size() != 1) {
        // Too many characters in field
        ss << "Invalid short answer question level " << tmp << ". ";
        ss << "Expected a number from 1 to 9.";
        throw(ss.str());
    }
    if (!std::isdigit(tmp.at(0))) {
        // We're expecting a digit
        ss << "Invalid short answer question level " << tmp << ". ";
        ss << "Expected a number from 1 to 9.";
        throw(ss.str());
    }
    int level = tmp.at(0) - '0';
    if (level < 1 || level > 9) {
        // Level out of acceptable bounds
        ss << "Invalid short answer question level " << tmp << ". ";
        ss << "Expected a number from 1 to 9.";
        throw(ss.str());
    }
    // Validate question text
    tmp = parts.at(2);
    if (tmp.empty()) {
        ss << "Expected a question. Received empty string.";
        throw(ss.str());
    }
    // Validate answer text
    tmp = parts.at(3);
    if (tmp.empty()) {
        ss << "Expected an answer. Received empty string.";
        throw(ss.str());
    }

    return true;
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
