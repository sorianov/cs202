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

std::vector<std::string> Quiz::explode(std::string str, char delimiter='|') {
    std::istringstream ss(str);
    std::string token;
    std::vector<std::string> parts;
    while(std::getline(ss, token, delimiter)) {
        parts.push_back(token);
    }
    return parts;
}

void Quiz::printQuizSummary() {
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
}

void Quiz::printQuizInstructions() {
    std::cout << "Hope your brain's warmed up, it's Quiz time!!!" << std::endl;
    std::cout << "After each answer is displayed, press enter to see the ";
    std::cout << "next question." << std::endl;
    std::cout << std::endl;
}

int Quiz::deliverQuiz() {
    std::string answer;

    printQuizInstructions();
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
    printQuizSummary();

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

bool Quiz::isComment(char c) {
    return c == '#';
}

bool Quiz::isQuestionCode(char c) {
    c = std::tolower(c);
    if (c == 's') {
        return true;
    }
    if (c == 't') {
        return true;
    }
    if (c == 'm') {
        return true;
    }
    return false;
}

bool Quiz::validateQuestionLine(std::string line) {
    // empty lines ok
    if (line.empty()) {
        return true;
    }

    const char firstChar = line.at(0);
    if (std::isspace(firstChar)) {
        return true;
    }
    if (isComment(firstChar)) {
        return true;
    }
    if (isQuestionCode(firstChar)) {
        return true;
    }

    return false;
}

void Quiz::printErrorMessage(int lineNumber, std::string line) {
    std::stringstream ss;
    ss << "Error while parsing " << filename << ":\n";
    ss << "\tInvalid character " << line.at(0);
    ss << " at line " << lineNumber << ".";
    std::cerr << ss.str() << std::endl;
}

bool Quiz::shouldSkipLine(int lineNumber, std::string line) {
    if (!validateQuestionLine(line)) {
        printErrorMessage(lineNumber, line);
        return true;
    }
    if (line.empty()) {
        return true;
    }
    if (isComment(line.at(0))) {
        return true;
    }
    if (std::isspace(line.at(0))) {
        return true;
    }
    return false;
}

bool Quiz::addQuestion(std::vector<std::string> lineParts) {
    std::string type = lineParts.at(0);
    Question* ptr = NULL;
    if (type.length() != 1) {
        std::cerr << "Couldn't determine question type. ";
        std::cerr << type << " is not a valid question code.";
        std::cerr << std::endl;
        return false;
    }
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
    questions.push_back(ptr);
    return true;
}

bool Quiz::loadQuestions(std::string filename) {
    int lineNumber = 0;
    std::ifstream f;
    f.open(filename.c_str());
    std::string line;
    std::vector<std::string> lineParts;
    if (f.is_open()) {
        questions.clear();
        this->filename = filename;
        filenameIsValid = true;
        while (std::getline(f, line)) {
            ++lineNumber;

            if (shouldSkipLine(lineNumber, line)) {
                continue;
            }
            lineParts = explode(line);

            if (lineParts.size() == 0) {
                std::cerr << "There was an issue loading question on line ";
                std::cerr << lineNumber;
                std::cerr << std::endl;
                continue;
            }

            try {
                if (!addQuestion(lineParts)) {
                    continue;
                }
            } catch (std::string e) {
                std::cerr << "An error ocurred on line " << lineNumber << ": ";
                std::cerr << e << std::endl;
                continue;
            }
        }
        f.close();
        return true;
    } else {
        this->filename = filename;
        filenameIsValid = false;
        f.close();
        throw("Could not open file for reading.");
    }
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
    printQuizSummary();

    return correct;

}
