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
