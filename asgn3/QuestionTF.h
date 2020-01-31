//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-29
// Title: Assignment 2: Inheritance and Polymorphism part 2
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#ifndef QUESTIONTF_H
#define QUESTIONTF_H

#include <string>
#include <vector>
#include "Question.h"

class QuestionTF : public Question {
    public:
        /**
         * Default Constructor
         */
        QuestionTF();
        /**
         * Constructor to set questionText and answerText
         *
         * @param std::string   String to use as questionText
         * @param std::string   String to use as answerText
         */
        QuestionTF(std::string, std::string);
        /**
         * Constructor for extracting questionText and answerText from a vector
         * full of tokens.
         *
         * @param std::vector<std::string>  Vector of tokens extracted from a
         *                                  questions file
         */
        QuestionTF(std::vector<std::string>);
        /**
         * Copy Constructor
         */
        QuestionTF(const QuestionTF&);
        /**
         * Assignment operator overload
         *
         * @param QuestionTF& Reference to object we should copy.
         *
         * @return QuestionTF& Reference to this object.
         */
        QuestionTF& operator=(const QuestionTF&);
        /**
         * Class destructor. Only here to fulfill Rule of Three. Has an empty
         * implementation.
         */
        virtual ~QuestionTF();
        /**
         * Prints the value of the questionText member variable.
         */
        virtual void showQuestion();
        /**
         * Prints the value of the answerText member variable.
         */
        virtual void showAnswer();
        /**
         * Compares the first character of the parameter string to the first
         * character of answerText member variable. Both strings are converted
         * to lowercase versions before being compared.
         *
         * @param std::string   String to compare to answerText
         * @return bool         True if the first characters in each string
         *                      match, false otherwise.
         */
        virtual bool checkAnswer(std::string);
};

#endif
