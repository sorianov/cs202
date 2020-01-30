#ifndef QUESTIONMC
#define QUESTIONMC

#include <vector>
#include <string>
#include "Question.h"

class QuestionMC : public Question {
    public:
        QuestionMC();
        QuestionMC(std::string, std::string);
        QuestionMC(std::vector<std::string>);
        virtual void showQuestion();
        virtual void showAnswer();
        virtual bool checkAnswer(std::string);
    private:
        std::vector<std::string> parts(std::string, char=':');
        std::vector<std::string> choices;
};

#endif
