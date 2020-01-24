#include "Quiz.h"
#include "Question.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: quiz filename [-d]";
        std:: cout << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    Quiz quiz;

    if (!quiz.loadQuestions(filename)) {
        std::cout << "Questions could not be loaded";
        std::cout << std::endl;
    }

    if (argc == 3) {
        std::string dumpFlag = argv[2];
        if (dumpFlag == "-d") {
            quiz.dumpQuestions();
            return 0;
        }
    }
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
