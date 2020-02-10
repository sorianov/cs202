//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-29
// Title: Assignment 2: Inheritance and Polymorphism part 2
// Description: Create a basic quiz application that can extended via
// inheritance in the future.
//----------------------------------------------------------------------------
#ifndef QUIZ_H
#define QUIZ_H

#include <vector>
#include <string>
#include "Question.h"

class Quiz {
    public:
        /**
         * Loads questions from a file
         *
         * @param std::string   Name of the file we're loading questions from
         *
         * @return bool True if the questions were successfully loaded, False
         *              if there was a problem loading the questions.
         */
        bool loadQuestions(std::string);
        /**
         * Dumps the loaded questions to stdout. Will first print the question
         * followed by the answer.
         */
        void dumpQuestions();
        /**
         * Prints questions and allows user to input answers.
         *
         * @return int  The number of questions the user answered correctly.
         */
        int deliverQuiz();
        /**
         * Default constructor.
         */
        Quiz();
        /**
         * Overloaded constructor that accepts a filename as a parameter.
         *
         * @param std::string   Name of file to load questions from.
         */
        Quiz(std::string);
        /**
         * Destructor. Will delete and clear pointers in the questions member
         * variable.
         */
        ~Quiz();
        /**
         * Copy constructor.
         *
         * @param Quiz& Reference to object we will copy.
         */
        Quiz(Quiz&);
        /**
         * Assignment operator overload.
         *
         * @param const Quiz&   Reference to object we will copy.
         *
         * @return Quiz&    A reference to this object.
         */
        Quiz& operator=(const Quiz&);
        /**
         * Getter function for the correct variable
         *
         * @returns int Value of correct member variable
         */
        int getNumCorrect();
        /**
         * Getter function for the incorrect variable
         *
         * @returns int Value of incorrect member variable
         */
        int getNumIncorrect();
        /**
         * Prompts the user to see if they would like to try the questions they
         * answered incorrectly again. Will deliver those questions if the user
         * responds with y.
         *
         * @returns int Value of correct member variable
         */
        int deliverIncorrectQuestions();
    private:
        /**
         * Parses a string and separates contents by a passed delimiter and
         * returns the parsed contents in a string vector. This function will
         * not return false. RAther, it will throw an exception instead.
         *
         * @param std::string   The string to parse
         * @param char          The character to use as a delimiter. '|' is
         *                      used by default.
         *
         * @return std::vector<std::string> Parts of the string that were
         *                                  separated by the delimiter.
         *
         */
        std::vector<std::string> parts(std::string, char);
        /**
         * Does some preliminary validation of a question data line before
         * feeding it into a Question subclass. This function will throw an
         * exception instead of returning false.
         *
         * @param std::string   Question data to validate
         *
         * @throws std::string  Exception with description of why it was
         *                      thrown.
         *
         * @return bool         True if the data passes validation.
         */
        bool validateQuestionLine(std::string);
        /**
         * Validates passed parameter string that should be a 'yes' or 'no'
         * response.
         *
         * @param std::string   The string to validate
         *
         * @outputs std::cout   A message explaining acceptable data.
         *
         * @returns             True if the parameter is a valid yes or no
         *                      answer. Returns false otherwise.
         */
        bool validateYesNo(std::string);
        std::vector<Question*> questions;
        std::vector<Question*> incorrectQuestions;
        std::string filename;
        int correct;
        int incorrect;
        bool filenameIsValid;
};

#endif
