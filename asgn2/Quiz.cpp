#include "Quiz.h"
#include "Question.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

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
        parts.push_back(token);
    }
    return parts;
}

int Quiz::deliverQuiz() {
    int correct = 0;
    std::string answer;
    std::cout << "Hope your brain's warmed up, it's Quiz time!!!" << std::endl;
    std::cout << "After each answer is displayed, press enter to see the ";
    std::cout << "next question." << std::endl;

    for (std::vector<Question>::iterator it = questions.begin();
            it != questions.end();
            ++it) {
        (*it).showQuestion();
        std::cout << "> ";
        std::cin >> answer;
        if((*it).checkAnswer(answer)) {
            std::cout << "Correct! Great job!" << std::endl;
            (*it).markCorrect();
            ++correct;
        } else {
            std::cout << "Sorry, the answer is ";
            (*it).showAnswer();
            std::cout << std::endl;
        }
    }

    float correctF = static_cast<float>(correct * 100);
    float totalF = static_cast<float>(questions.size() * 100);
    float percentage = (correctF / totalF) * 100.0;

    std::cout << std::fixed;
    std::cout << std::setprecision(0);
    std::cout << "You got " << correct << " of " << questions.size() << " ";
    std::cout << "correct: " << percentage << "%." << std::endl;

    return correct;
}

void Quiz::dumpQuestions() {
    for (std::vector<Question>::iterator it = questions.begin();
            it != questions.end(); ++it) {
        (*it).showQuestion();
        (*it).showAnswer();
    }
}

bool Quiz::loadQuestions(std::string filename) {
    std::ifstream f;
    f.open(filename);
    std::string line;
    std::string question;
    std::string answer;
    std::vector<std::string> lineParts;
    if (f.is_open()) {
        while (std::getline(f, line)) {
            lineParts = parts(line);
            question = lineParts[2];
            answer = lineParts[3];
            Question q(question, answer);
            questions.push_back(q);
        }
        return true;
    }

    return false;
}
