//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-02-09
// Title: Assignment 3: Abstract classes, exceptions, and other error handling
// Description: Create a basic and robust quiz application that can extended
// via inheritance in the future.
//----------------------------------------------------------------------------
#include <iostream>
#include <sstream>
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
    validateQuestionLineParts(lineParts);
    /*
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
    */
    questionText = lineParts[2];
    answerText = lineParts[3];
    correct = false;
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

// TODO Make custom exceptions for less repetitive code.
bool QuestionTF::validateQuestionLineParts(std::vector<std::string> parts) {
    std::stringstream ss;
    std::string tmp;
    // Make sure we have a correct vector size before we start accessing
    // out of bound members.
    if (parts.size() > 4) {
        ss << "Invalid number of true/false question parameters. There are ";
        ss << "too many fields separated by '|' characters. ";
        ss << "Expected format:\n";
        ss << "\tT|level|question|answer";
        throw(ss.str());
    }
    if (parts.size() < 4) {
        ss << "Invalid number of true/false question parameters. There are ";
        ss << "too few fields separated by '|' characters. ";
        ss << "Expected format:\n";
        ss << "\tT|level|question|answer";
        throw(ss.str());
    }
    // Validate Question code
    tmp = parts.at(0);
    if (tmp.size() != 1) {
        // Too many characters in field
        ss << "Invalid true/false question code " << tmp << ". ";
        ss << "Expected T.";
        throw(ss.str());
    }

    tmp = toLower(tmp);
    if (tmp != "t") {
        // Wrong code
        ss << "Invalid true/false question code " << tmp << ". ";
        ss << "Expected T.";
        throw(ss.str());
    }
    // Validate Level
    tmp = parts.at(1);
    if (tmp.size() != 1) {
        // Too many characters in field
        ss << "Invalid true/false question level " << tmp << ". ";
        ss << "Expected a number from 1 to 9.";
        throw(ss.str());
    }
    if (!std::isdigit(tmp.at(0))) {
        // We're expecting a digit
        ss << "Invalid true/false question level " << tmp << ". ";
        ss << "Expected a number from 1 to 9.";
        throw(ss.str());
    }
    int level = tmp.at(0) - '0';
    if (level < 1 || level > 9) {
        // Level out of acceptable bounds
        ss << "Invalid true/false question level " << tmp << ". ";
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
    tmp = toLower(tmp);
    if (tmp.at(0) != 'f' && tmp.at(0) != 't') {
        ss << "Expected True or False as an answer.";
        throw(ss.str());
    }

    return true;
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
