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
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Quiz.h"
#include "Question.h"
#include "QuestionTF.h"
#include "QuestionMC.h"

Quiz::Quiz() {
    questions = std::vector<Question*>();
}

Quiz::Quiz(std::string filename) {
    questions = std::vector<Question*>();
    loadQuestions(filename);
}

Quiz::~Quiz() {
    for (std::vector<Question*>::iterator it = questions.begin();
            it != questions.end();
            ++it) {
        delete (*it);
    }
    questions.clear();
}

Quiz::Quiz(Quiz& q) {
    for (std::vector<Question*>::iterator it = q.questions.begin();
            it != q.questions.end();
            ++it) {
        questions.push_back((*it));
    }
}

Quiz& Quiz::operator=(const Quiz& q) {
    for (std::vector<Question*>::const_iterator it = q.questions.begin();
            it != q.questions.end();
            ++it) {
        questions.push_back((*it));
    }
    return *this;
}

std::vector<std::string> Quiz::parts(std::string str, char delimiter='|') {
    std::istringstream ss(str);
    std::string token;
    std::vector<std::string> parts;
    while(std::getline(ss, token, delimiter)) {
        parts.push_back(token);
    }
    return parts;
}

int Quiz::deliverQuiz() {
    int correct = 0;
    std::string answer;
    std::cout << "Hope your brain's warmed up, it's Quiz time!!!" << std::endl;
    std::cout << "After each answer is displayed, press enter to see the ";
    std::cout << "next question." << std::endl;
    std::cout << std::endl;

    for (std::vector<Question*>::iterator it = questions.begin();
            it != questions.end();
            ++it) {
        (*it)->showQuestion();
        std::cout << "> ";
        std::getline(std::cin, answer);
        if((*it)->checkAnswer(answer)) {
            std::cout << "Correct! Great job!" << std::endl;
            std::cout << std::endl;
            (*it)->markCorrect();
            ++correct;
        } else {
            std::cout << "Sorry, the answer is ";
            (*it)->showAnswer();
            std::cout << std::endl;
        }
    }

    int totalQuestions = static_cast<int>(questions.size());
    float correctF = static_cast<float>(correct * 100);
    float totalF = static_cast<float>(totalQuestions * 100);
    float percentage = (correctF / totalF) * 100.0;

    std::cout << std::fixed;
    std::cout << std::setprecision(0);
    std::cout << "You got " << correct << " of " << questions.size() << " ";
    std::cout << "correct: " << percentage << "%. ";
    if (correct < totalQuestions) {
        std::cout << "Better study more!";
    }

    if (correct == totalQuestions) {
        std::cout << "Motivational text.";
    }

    std::cout << std::endl;

    return correct;
}

void Quiz::dumpQuestions() {
    for (std::vector<Question*>::iterator it = questions.begin();
            it != questions.end(); ++it) {
        (*it)->showQuestion();
        std::cout << "> ";
        (*it)->showAnswer();
    }
}

bool Quiz::loadQuestions(std::string filename) {
    const char* fn = filename.c_str();
    std::ifstream f;
    f.open(fn);
    std::string type;
    std::string line;
    std::vector<std::string> lineParts;
    if (f.is_open()) {
        while (std::getline(f, line)) {
            lineParts = parts(line);

            if (lineParts.size() == 0) {
                std::cerr << "There was an issue loading questions";
                std::cerr << std::endl;
                return false;
            }

            type = lineParts[0];
            if (type.length() != 1) {
                std::cerr << "Couldn't determine question type";
                std::cerr << std::endl;
                return false;
            }

            Question* ptr = NULL;
            if (type == "S") {
                // Short answer questions
                ptr = new Question(lineParts);
            } else if (type == "T") {
                // True/False questions
                ptr = new QuestionTF(lineParts);
            } else if (type == "M") {
                // Multiple choice questions
                ptr = new QuestionMC(lineParts);
            } else {
                std::cerr << "Couldn't determine question type";
                std::cerr << std::endl;
                return false;
            }

            if (ptr == NULL) {
                std::cerr << "Couldn't add question to quiz.";
                std::cerr << std::endl;
                return false;
            }

            questions.push_back(ptr);
        }
        f.close();
        return true;
    }
    f.close();
    return false;
}
