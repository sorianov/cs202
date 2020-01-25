#ifndef QUIZ_H
#define QUIZ_H

#include "Question.h"
#include <vector>
#include <string>

class Quiz {
    public:
        bool loadQuestions(std::string);
        void dumpQuestions();
        int deliverQuiz();
        Quiz();
        Quiz(std::string);
    private:
        std::vector<std::string> parts(std::string, char);
        std::vector<Question> questions;
};

#endif
