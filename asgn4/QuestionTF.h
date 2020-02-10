//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-02-09
// Title: Assignment 3: Abstract classes, exceptions, and other error handling
// Description: Create a basic and robust quiz application that can extended
// via inheritance in the future.
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
    protected:
        /**
         * Validate questions tokens for bad data.
         *
         * @param std::vector<std::string>> Vector containing tokens to
         *                                  validate.
         *
         * @throws std::string              Exception with a description of
         *                                  why it was thrown
         *
         * @return bool                     True is every token passes
         *                                  validation.
         */
        virtual bool validateQuestionLineParts(std::vector<std::string>);
};

#endif
