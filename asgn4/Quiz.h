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
        int getNumCorrect();
        int getNumIncorrect();
        int deliverIncorrectQuestions();
    private:
        /**
         * Parses a string and separates contents by a passed delimiter and
         * returns the parsed contents in a string vector.
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
        bool validateQuestionLine(std::string);
        bool validateYesNo(std::string);
        std::vector<Question*> questions;
        std::vector<Question*> incorrectQuestions;
        std::string filename;
        int correct;
        int incorrect;
        bool filenameIsValid;
};

#endif
