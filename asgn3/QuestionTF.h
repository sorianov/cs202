#ifndef QUESTIONTF_H
#define QUESTIONTF_H

#include <string>
#include "Question.h"

class QuestionTF : public Question {
    public:
        QuestionTF();
        QuestionTF(std::string, std::string);
        void showQuestion();
        void showAnswer();
        bool checkAnswer(std::string);
};

#endif
