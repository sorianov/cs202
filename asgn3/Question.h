//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-24
// Title: Assignment 2: Inheritance and Polymorphism part 1
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>

class Question {
    public:
        /**
         * Prints questionText to stdout.
         */
        virtual void showQuestion();
        /**
         * Compares the parameter to answerText
         *
         * @param std::string   The string to compare against answerText
         */
        virtual bool checkAnswer(std::string);
        /**
         * Returns value of correct private member variable
         *
         * @return bool Value of correct private member variable
         */
        bool isCorrect();
        /**
         * Prints answerText to stdout
         */
        virtual void showAnswer();
        /**
         * Changes value of the correct private member variable to true.
         */
        void markCorrect();
        /**
         * Default constructor
         */
        Question();
        /**
         * Overloaded constructor.
         *
         * @param std::string   String to use as questionText.
         * @param std::string   String to use as answerText.
         */
        Question(std::string, std::string);
        Question(std::vector<std::string>);
        virtual ~Question();
        Question(Question&);
        Question& operator=(Question&);
    protected:
        std::string questionText;
        std::string answerText;
        bool correct;
};

#endif
