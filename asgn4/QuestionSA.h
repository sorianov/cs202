//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-02-09
// Title: Assignment 3: Abstract classes, exceptions, and other error handling
// Description: Create a basic and robust quiz application that can extended
// via inheritance in the future.
//----------------------------------------------------------------------------
#ifndef QUESTIONSA_H
#define QUESTIONSA_H

#include <string>
#include <vector>
#include "Question.h"

class QuestionSA : public Question {
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
        void markCorrect(); /**
         * Default constructor
         */
        QuestionSA();
        /**
         * Overloaded constructor for initializing questionText and answerText
         * member variables.
         *
         * @param std::string   String to use as questionText.
         * @param std::string   String to use as answerText.
         */
        QuestionSA(std::string, std::string);
        /**
         * Constructor for extracting questionText and answerText from a vector
         * of string tokens.
         *
         * @param std::vector<std::string>  Vector of tokens extracted from a
         *                                  questions file
         */
        QuestionSA(std::vector<std::string>);
        /**
         * Copy constructor
         *
         * @param QuestionSA& Reference to object we should copy.
         */
        QuestionSA(QuestionSA&);
        /**
         * Virtual destructor in case this class is ever inherited.
         */
        virtual ~QuestionSA();
        /**
         * Assignment operator overload
         *
         * @param QuestionSA& Reference to object we should copy.
         *
         * @return QuestionSA& Reference to this object.
         */
        QuestionSA& operator=(const QuestionSA&);
    protected:
        /**
         * Removes all space characters in a string.
         *
         * @param std::string   String to remove space characters from.
         *
         * @return std::string  String with removed space characters.
         */
        std::string removeSpaces(std::string);
        /**
         * Make a string lowercase.
         *
         * @param std::string   String to make lowercase.
         *
         * @see https://notfaq.wordpress.com/2007/08/04/
         *          cc-convert-string-to-upperlower-case/
         *
         * @return std::string Lowercase version of passed string.
         */
        std::string toLower(std::string);
        /**
         * To be used as a callback for a std::transform call
         *
         * @param unsigned char An unsigned character
         *
         * @return unsigned char std::tolower() of parameter
         */
        static unsigned char lower(unsigned char);
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
        std::string questionText;
        std::string answerText;
        bool correct;
};

#endif
