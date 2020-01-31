#ifndef QUESTIONTF_H
#define QUESTIONTF_H

#include <string>
#include <vector>
#include "Question.h"

class QuestionTF : public Question {
    public:
        QuestionTF();
        QuestionTF(std::string, std::string);
        QuestionTF(std::vector<std::string>);
        QuestionTF(const QuestionTF&);
        QuestionTF& operator=(const QuestionTF&);
        virtual ~QuestionTF();
        virtual void showQuestion();
        virtual void showAnswer();
        virtual bool checkAnswer(std::string);
};

#endif
