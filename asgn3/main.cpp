//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-24
// Title: Assignment 2: Inheritance and Polymorphism part 1
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#include "Question.h"
#include "QuestionTF.h"
#include "Quiz.h"
#include <iostream>

void printUsage() {
    std::cerr << "Usage: quiz filename [-d]";
    std::cerr << std::endl;
}

int main(int argc, char* argv[]) {
    QuestionTF qt("True or False", "True");
    std::string fakeAnswer = "t";
    qt.showQuestion();
    qt.showAnswer();
    if (qt.checkAnswer(fakeAnswer)) {
        std::cout << "correct" << std::endl;
    } else {
        std::cout << "wrong" << std::endl;
    }
    return 0;
    if (argc < 2) {
        printUsage();
        return 1;
    }
    std::string filename = argv[1];
    Quiz quiz;

    if (!quiz.loadQuestions(filename)) {
        std::cerr << "Questions could not be loaded";
        std::cerr << std::endl;
        return 3;
    }

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
    return 0;
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
