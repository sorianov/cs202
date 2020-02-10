//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-02-09
// Title: Assignment 3: Abstract classes, exceptions, and other error handling
// Description: Create a basic and robust quiz application that can extended
// via inheritance in the future.
//----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Quiz.h"

void printUsage() {
    std::cerr << "Usage: quiz filename [-d]";
    std::cerr << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }
    std::string filename = argv[1];
    try {
        Quiz quiz(filename);
        if (argc == 3) {
            std::string dumpFlag = argv[2];
            if (dumpFlag == "-d") {
                quiz.dumpQuestions();
                return 0;
            } else {
                printUsage();
                return 2;
            }
        }

        quiz.deliverQuiz();

        int incorrect = quiz.getNumIncorrect();
        std::string retryAnswer;
        if (incorrect > 0) {
            quiz.deliverIncorrectQuestions();
        }
        return 0;
    } catch (const char* e) {
        std::cerr << e << std::endl;
        return 3;
    } catch (...) {
        std::cerr << "An Unknown error ocurred. Exiting." << std::endl;
        return 4;
    }
}

/* main test code */
/*
    std::string question = "question 1";
    std::string badAnswer = "no";
    std::string goodAnswer = "yes";
    Question q(question, goodAnswer);
    q.showQuestion();
    q.showAnswer();

    if (q.checkAnswer(badAnswer)) {
        std::cout << "bad answer good" << std::endl;
    }
    if (q.isCorrect()) {
        std::cout << "question correct" << std::endl;
    }
    if (q.checkAnswer(goodAnswer)) {
        std::cout << "good answer good" << std::endl;
        q.markCorrect();
    }
    if (q.isCorrect()) {
        std::cout << "question correct" << std::endl;
    }

    Quiz quiz;
    std::cout << "Loading questions:" << std::endl;
    quiz.loadQuestions("questions.txt");
    std::cout << "End Loading questions:" << std::endl;
    std::cout << "Dumping questions:" << std::endl;
    quiz.dumpQuestions();
    std::cout << "End Dumping questions:" << std::endl;
    return 1;
    */
