#include "Quiz.h"
#include "Question.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

Quiz::Quiz() {
    std::vector<Question> questions;
}

Quiz::Quiz(std::string filename) {
    std::vector<Question> questions;
    loadQuestions(filename);
}

std::vector<std::string> Quiz::parts(std::string str, char delimiter='|') {
    std::istringstream ss(str);
    std::string token;
    std::vector<std::string> parts;
    while(std::getline(ss, token, delimiter)) {
        //std::cout << token << std::endl;
        parts.push_back(token);
    }
    return parts;
}

void Quiz::dumpQuestions() {
    for (std::vector<Question>::iterator it = questions.begin();
            it != questions.end();
            ++it) {
        (*it).showQuestion();
        (*it).showAnswer();
    }
}

bool Quiz::loadQuestions(std::string filename) {
    std::ifstream f;
    f.open(filename);
    std::string line;
    std::vector<std::string> lineParts;
    if (f.is_open()) {
        while (std::getline(f, line)) {
            lineParts = parts(line); 
            Question q(lineParts[2], lineParts[3]);
            questions.push_back(q);
        }
        return true;
    }

    return false;
}
