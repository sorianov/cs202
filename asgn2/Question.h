#ifndef QUESTION_H
#define QUESTION_H

#include <string>

class Question {
    public:
        void showQuestion();
        bool checkAnswer(std::string);
        bool isCorrect();
        void showAnswer();
        void markCorrect();
        Question();
        Question(std::string, std::string);
    private:
        std::string toLower(std::string);
        std::string questionText;
        std::string answerText;
        bool correct;
};

#endif
