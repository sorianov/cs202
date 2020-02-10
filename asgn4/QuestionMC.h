//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-02-09
// Title: Assignment 3: Abstract classes, exceptions, and other error handling
// Description: Create a basic and robust quiz application that can extended
// via inheritance in the future.
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
        /**
         * Validates the tokens inside the passed vector parameter. This
         * function will not return false. It will throw an exception instread.
         *
         * @param std::vector<std::string>  Vector containing tokens to
         *                                  validate
         *
         * @throws  std::string             Exception with a description of why
         *                                  it was thrown.
         *
         * @return  bool                    True if every token passes
         *                                  validation.
         */
        bool validateChoices(std::vector<std::string>);
        std::vector<std::string> choices;
};

#endif
