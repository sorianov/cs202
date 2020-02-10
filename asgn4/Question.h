//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-02-09
// Title: Assignment 3: Abstract classes, exceptions, and other error handling
// Description: Create a basic and robust quiz application that can extended
// via inheritance in the future.
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
        virtual void showQuestion() = 0;
        /**
         * Compares the parameter to answerText
         *
         * @param std::string   The string to compare against answerText
         */
        virtual bool checkAnswer(std::string) = 0;
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
         * Overloaded constructor for initializing questionText and answerText
         * member variables.
         *
         * @param std::string   String to use as questionText.
         * @param std::string   String to use as answerText.
         */
        Question(std::string, std::string);
        /**
         * Constructor for extracting questionText and answerText from a vector
         * of string tokens.
         *
         * @param std::vector<std::string>  Vector of tokens extracted from a
         *                                  questions file
         */
        Question(std::vector<std::string>);
        /**
         * Copy constructor
         *
         * @param Question& Reference to object we should copy.
         */
        Question(Question&);
        /**
         * Virtual destructor in case this class is ever inherited.
         */
        virtual ~Question();
        /**
         * Assignment operator overload
         *
         * @param Question& Reference to object we should copy.
         *
         * @return Question& Reference to this object.
         */
        Question& operator=(const Question&);
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
         * @return std::strign Lowercase version of passed string.
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
         * Validate questions tokens for bad data. This function will not
         * return false. Rather, it will throw an exception instead.
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
        virtual bool validateQuestionLineParts(std::vector<std::string>) = 0;
        std::string questionText;
        std::string answerText;
        bool correct;
};

#endif
