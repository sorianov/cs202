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
#include <cctype>
#include "Quiz.h"
#include "Question.h"
#include "QuestionSA.h"
#include "QuestionTF.h"
#include "QuestionMC.h"

Quiz::Quiz() {
    questions = std::vector<Question*>();
    incorrectQuestions = std::vector<Question*>();
    correct = 0;
    incorrect = 0;
    filenameIsValid = false;
    filename = "";
}

Quiz::Quiz(std::string filename) {
    questions = std::vector<Question*>();
    incorrectQuestions = std::vector<Question*>();
    correct = 0;
    incorrect = 0;
    this->filename = filename;
    filenameIsValid = false;
    loadQuestions(filename);
}

Quiz::~Quiz() {
    for (std::vector<Question*>::iterator it = questions.begin();
            it != questions.end();
            ++it) {
        delete (*it);
    }
    questions.clear();
    incorrectQuestions.clear();
}

Quiz::Quiz(Quiz& q) {
    for (std::vector<Question*>::iterator it = q.questions.begin();
            it != q.questions.end();
            ++it) {
        questions.push_back((*it));
    }
    correct = 0;
    incorrect = 0;
    filename = q.filename;
    filenameIsValid = q.filenameIsValid;
}

Quiz& Quiz::operator=(const Quiz& q) {
    for (std::vector<Question*>::const_iterator it = q.questions.begin();
            it != q.questions.end();
            ++it) {
        questions.push_back((*it));
    }
    correct = 0;
    incorrect = 0;
    filename = q.filename;
    filenameIsValid = q.filenameIsValid;
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
            ++correct;
            std::cout << "Correct! Great job!" << std::endl;
            std::cout << std::endl;
            (*it)->markCorrect();
        } else {
            ++incorrect;
            incorrectQuestions.push_back((*it));
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

bool Quiz::validateQuestionLine(std::string line) {
    // empty lines ok
    if (line == "") {
        return true;
    }
    if (line.size() == 0) {
        return true;
    }

    const char lineChar = std::tolower(line.at(0));
    if (std::isspace(lineChar)) {
        return true;
    }
    if (lineChar == '#') {
        return true;
    }
    if (lineChar == 's') {
        return true;
    }
    if (lineChar == 't') {
        return true;
    }
    if (lineChar == 'm') {
        return true;
    }

    return false;
}

bool Quiz::loadQuestions(std::string filename) {
    const char* fn = filename.c_str();
    int lineNumber = 0;
    std::ifstream f;
    f.open(fn);
    std::string type;
    std::string line;
    std::vector<std::string> lineParts;
    if (f.is_open()) {
        if (questions.size() > 0) {
            questions.clear();
        }
        this->filename = filename;
        filenameIsValid = true;
        while (std::getline(f, line)) {
            ++lineNumber;
            if (!validateQuestionLine(line)) {
                std::stringstream ss;
                ss << "Error while parsing " << filename << ":\n";
                ss << "\tInvalid character " << line.at(0);
                ss << " at line " << lineNumber << ".";
                std::cerr << ss.str() << std::endl;
                continue;
            }
            if (line == "") {
                continue;
            } else if (line.size() > 0) {
                if (line.at(0) == '#') {
                    continue;
                } else if (std::isspace(line.at(0))) {
                    continue;
                }
            }
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
                ptr = new QuestionSA(lineParts);
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
    } else {
        this->filename = filename;
        filenameIsValid = false;
        throw("Could not open file for reading.");
    }
    f.close();
    return false;
}

int Quiz::getNumCorrect() {
    return correct;
}

int Quiz::getNumIncorrect() {
    return incorrect;
}

bool Quiz::validateYesNo(std::string str) {
    if (str == "") {
        return true;
    }

    char lChar;
    try {
       lChar = std::tolower(str.at(0));
       if (lChar == 'y') {
            return true;
       }
       if (lChar == 'n') {
            return true;
        }
    } catch (const std::out_of_range& oor) { }
    std::cout << "Please enter 'y' or 'n'";
    std::cout << std::endl;
    return false;
}

int Quiz::deliverIncorrectQuestions() {
    std::string answer;
    std::string retryAnswer;
    //int totalIncorrect = incorrectQuestions.size();
    do {
        std::cout << "You answered " << incorrect << " questions ";
        std::cout << "incorrectly. ";
        std::cout << "Would you like to repeat them? [Y/n]" << std::endl;
        std::getline(std::cin, retryAnswer);
    } while (!validateYesNo(retryAnswer));

    if (retryAnswer.size() > 0) {
        if (retryAnswer.at(0) == 'n') {
            return correct;
        }
    }

    std::vector<Question*>::iterator it = incorrectQuestions.begin();
    while(incorrect > 0) {
        if (it == incorrectQuestions.end()) {
            do {
                std::cout << "You still have incorrectly answered questions. ";
                std::cout << "Would you like to keep trying? [Y/n]";
                std::cout << std::endl;
                std::getline(std::cin, retryAnswer);
            } while (!validateYesNo(retryAnswer));

            if (retryAnswer.size() > 0) {
                if (retryAnswer.at(0) == 'n') {
                    break;
                }
            }

            it = incorrectQuestions.begin();
        }

        (*it)->showQuestion();
        std::cout << "> ";
        std::getline(std::cin, answer);

        if((*it)->checkAnswer(answer)) {
            --incorrect;
            ++correct;

            std::cout << "Correct! Great job!" << std::endl;
            std::cout << std::endl;

            (*it)->markCorrect();
            incorrectQuestions.erase(it);
            --it; // we resized the vector
        } else {
            std::cout << "Sorry, incorrect.\n" << std::endl;
        }
        ++it;
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
