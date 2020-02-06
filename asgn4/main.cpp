//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-29
// Title: Assignment 2: Inheritance and Polymorphism part 2
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
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
        /*
        if (!quiz.loadQuestions(filename)) {
            std::cerr << "Questions could not be loaded";
            std::cerr << std::endl;
            return 3;
        }
        */

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
            // start incorrect loop
            std::cout << "You answered " << incorrect << " questions ";
            std::cout << "incorrectly. ";
            std::cout << "Would you like to repeat them? [Y/n]" << std::endl;
            std::getline(std::cin, retryAnswer);
            if (retryAnswer == ""
                    || retryAnswer.at(0) == 'y'
                    || retryAnswer.at(0) == 'Y') {
                // serve incorrect questions.
                quiz.deliverIncorrectQuestions();
            }
        }
        return 0;
    } catch (const char* e) {
        std::cerr << e << std::endl;
        return 3;
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
