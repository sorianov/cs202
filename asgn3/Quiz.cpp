//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-24
// Title: Assignment 2: Inheritance and Polymorphism part 1
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#include "Quiz.h"
#include "Question.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

Quiz::Quiz() {
    questions = std::vector<Question*>();
}

Quiz::Quiz(std::string filename) {
    questions = std::vector<Question*>();
    loadQuestions(filename);
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
        std::cin >> answer;
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
                ptr = new Question(lineParts);
            } else if (type == "T") {
                // True/False questions
                ptr = new Question(lineParts);
            } else if (type == "M") {
                // Multiple choice questions
                ptr = new Question(lineParts);
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
