//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-29
// Title: Assignment 2: Inheritance and Polymorphism part 2
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
#include "QuestionMC.h"

QuestionMC::QuestionMC() {
   questionText = "";
   answerText = "";
   correct = false;
}

QuestionMC::QuestionMC(std::string question, std::string answer) {
    questionText = question;
    answerText = answer;
}

QuestionMC::QuestionMC(std::vector<std::string> lineParts) {
    if (lineParts.size() != 5) {
        std::cerr << "Invalid number of true/false question parameters";
        std::cerr << std::endl;
        questionText = "";
        answerText = "";
        correct = false;
    } else {
        questionText = lineParts[2];
        answerText = lineParts[4];
        choices = parts(lineParts[3]);
        correct = false;
    }
}

QuestionMC::QuestionMC(const QuestionMC& q) {
    answerText = q.questionText;
    questionText = q.answerText;
    correct = q.correct;

    for (unsigned int i = 0; i < q.choices.size(); ++i) {
        choices.push_back(q.choices[i]);
    }
}

QuestionMC::~QuestionMC() { }

// TODO Make custom exceptions for less repetitive code.
bool QuestionMC::validateQuestionLineParts(std::vector<std::string> lParts) {
    std::stringstream ss;
    std::string tmp;
    // Make sure we have a correct vector size before we start accessing
    // out of bound members.
    if (lParts.size() > 5) {
        ss << "Invalid number of multiple choice question parameters. ";
        ss << "There are too many fields separated by '|' characters. ";
        ss << "Expected format:\n";
        ss << "\tM|level|question|possible:answers:to:question|letter";
        ss << "There can only be a maximum of 10 choices with a 2 choice ";
        ss << "minimum. For a 2 choice question, the answer can be either a ";
        ss << "or b, and for a 10 choice question, the answer can be a-j";
        throw(ss.str());
    }
    if (lParts.size() < 5) {
        ss << "Invalid number of multiple choice question parameters. ";
        ss << "There are too few fields separated by '|' characters. ";
        ss << "Expected format:\n";
        ss << "\tM|level|question|possible:answers:to:question|letter";
        ss << "There can only be a maximum of 10 choices with a 2 choice ";
        ss << "minimum. For a 2 choice question, the answer can be either a ";
        ss << "or b, and for a 10 choice question, the answer can be a-j";
        throw(ss.str());
    }
    // Validate Question code
    tmp = lParts.at(0);
    if (tmp.size() != 1) {
        // Too many characters in field
        ss << "Invalid multiple choice question code " << tmp << ". ";
        ss << "Expected M.";
        throw(ss.str());
    }
    
    tmp = toLower(tmp);
    if (tmp != "m") {
        // Wrong code
        ss << "Invalid multiple choice question code " << tmp << ". ";
        ss << "Expected M.";
        throw(ss.str());
    }
    // Validate Level
    tmp = lParts.at(1);
    if (tmp.size() != 1) {
        // Too many characters in field
        ss << "Invalid multiple choice question level " << tmp << ". ";
        ss << "Expected a number from 1 to 9.";
        throw(ss.str());
    }
    if (!std::isdigit(tmp.at(0))) {
        // We're expecting a digit
        ss << "Invalid multiple choice question level " << tmp << ". ";
        ss << "Expected a number from 1 to 9.";
        throw(ss.str());
    }
    int level = tmp.at(0) - '0';
    if (level < 1 || level > 9) {
        // Level out of acceptable bounds
        ss << "Invalid multiple choice question level " << tmp << ". ";
        ss << "Expected a number from 1 to 9.";
        throw(ss.str());
    }
    // Validate question text
    tmp = lParts.at(2);
    if (tmp.empty()) {
        ss << "Expected a question. Received empty string.";
        throw(ss.str());
    }
    // Validate choices
    std::vector<std::string> _choices = parts(lParts.at(3));
    validateChoices(_choices);

    // Validate answer letter
    int maxIndex = _choices.size() - 1;
    tmp = lParts.at(4);
    if (tmp.size() != 1 || tmp.empty()) {
        ss << "Expected a single letter. Got " << tmp << ".";
        throw(ss.str());
    }
    char c = tmp.at(0);
    if (!std::isalpha(c)) {
        ss << "Expected an ASCII alphabetical character";
        throw(ss.str());
    }
    char answer = std::tolower(tmp.at(0)) - 'a';
    if (answer < 0) {
        ss << "Answer is outside of possibilities. Nice quiz.";
        throw(ss.str());
    }
    if (answer > maxIndex) {
        ss << "Answer is outside of possibilities. Nice quiz.";
        throw(ss.str());
    }
    //TODO Test this code

    /*
    tmp = lParts.at(3);
    if (tmp.empty()) {
        ss << "Expected an answer. Received empty string.";
        throw(ss.str());
    }
    tmp = toLower(tmp);
    if (tmp.at(0) != 'f' && tmp.at(0) != 't') {
        ss << "Expected True or False as an answer.";
        throw(ss.str());
    }
    */

    return true;
}

bool QuestionMC::validateChoices(std::vector<std::string> _choices) {
    std::stringstream ss;
    int size = _choices.size();
    if (size < 2) {
       ss << "Too few choices. Minimum choice amount 2";
       throw(ss.str());
    }
    if (size > 10) {
       ss << "Too many choices. Maximum choice amount 10";
       throw(ss.str());
    }
    for (int i = 0; i < size; ++i) {
        if (_choices[i].empty()) {
            ss << "Received empty answer.";
            throw(ss.str());
        }
    }
    return true;
}

void QuestionMC::showQuestion() {
    char optionChar = 'a';
    std::cout << questionText;
    std::cout << "?";
    std::cout << std::endl;
    for (unsigned int i = 0; i < choices.size(); ++i) {
        std::cout << std::setw(3);
        std::cout << optionChar << ") ";
        std::cout << choices[i] << std::endl;
        ++optionChar;
    }
}

void QuestionMC::showAnswer() {
    std::cout << answerText << std::endl;
}

bool QuestionMC::checkAnswer(std::string answer) {
    char c = std::tolower(answer.c_str()[0]);
    char a = std::tolower(answerText.c_str()[0]);

    return c == a;
}

std::vector<std::string> QuestionMC::parts(std::string str, char delimiter) {
    std::istringstream ss(str);
    std::string token;
    std::vector<std::string> parts;
    while(std::getline(ss, token, delimiter)) {
        parts.push_back(token);
    }
    return parts;
}
