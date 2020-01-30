#ifndef QUESTIONMC
#define QUESTIONMC

#include <vector>
#include <string>
#include "Question.h"

class QuestionMC : public Question {
    public:
        QuestionMC();
        QuestionMC(std::string, std::string);
        void showQuestion();
        void showAnswer();
        bool checkAnswer(std::string);
    private:
        std::vector<std::string> choices;
};

#endif
