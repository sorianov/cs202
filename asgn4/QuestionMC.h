//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-29
// Title: Assignment 2: Inheritance and Polymorphism part 2
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#ifndef QUESTIONMC
#define QUESTIONMC

#include <vector>
#include <string>
#include "Question.h"

class QuestionMC : public Question {
    public:
        /**
         * Default constructor
         */
        QuestionMC();
        /**
         * Constructor to set questionText and answerText
         *
         * @param std::string   questionText value
         * @param std::string   answerText value
         */
        QuestionMC(std::string, std::string);
        /**
         * Constructor for extracting questionText and answerText from a vector
         * full of tokens.
         *
         * @param std::vector<std::string>  Vector of tokens extracted from a
         *                                  questions file
         */
        QuestionMC(std::vector<std::string>);
        /**
         * Copy constructor
         *
         * @param const QuestionMC& Reference to object that we should copy.
         */
        QuestionMC(const QuestionMC&);
        /**
         * Assignment operator overload
         *
         * @param const QuestionMC& Reference to object that we should copy.
         *
         * @return QuestionMC& Reference to *this
         */
        QuestionMC& operator=(const QuestionMC&);
        /**
         * Destructor. Clears choices member variable.
         */
        virtual ~QuestionMC();
        /**
         * Prints questionText along with the tokens in the choices member
         * variable to stdout.
         */
        virtual void showQuestion();
        /**
         * Prints answerText member variable to stdout.
         */
        virtual void showAnswer();
        /**
         * Checks if the lowercase first character of parameter is equal to the
         * lowercase first character of answerText member variable.
         *
         * @param std::string   String to compare against answerText member
         *                      variable
         *
         * @return bool         True if characters match, false otherwise.
         */
        virtual bool checkAnswer(std::string);
    protected:
        virtual bool validateQuestionLineParts(std::vector<std::string>);
    private:
        /**
         * Parses a string and separates contents by a passed delimiter and
         * returns the parsed contents in a string vector.
         *
         * @param std::string   The string to parse
         * @param char          The character to use as a delimiter. ':' is
         *                      used by default.
         *
         * @return std::vector<std::string> Parts of the string that were
         *                                  separated by the delimiter.
         *
         */
        std::vector<std::string> parts(std::string, char=':');
        std::vector<std::string> choices;
};

#endif
