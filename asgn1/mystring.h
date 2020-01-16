//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2020-01-15
// Title: Assignment 1: Operator Overloading
// Description: A basic string class
//----------------------------------------------------------------------------
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

using namespace std;

class MyString {
    private:
        char* data;
        int length;
        static bool printAsUppercase; // initialize to false. if true, outputs
                                      // all strings as uppercase
    public:
        /**
         * Default Constructor
         */
        MyString();
        /**
         * Overloaded constructor that accepts a character array.
         *
         * @param char* Pointer to character array which will deep copied to
         *              data member
         */
        MyString(char*);
        /**
         * Copy Constructor. Will deep copy MyString parameter to this
         *
         * @param MyString& A reference to the object we should copy.
         */
        MyString(MyString&);
        /**
         * Destructor. Will deallocate data member if necessary.
         */
        ~MyString();
        /**
         * Binary + operator overload. Will concatenate the data members of
         * this and the passed in reference. Returns a new MyString object with
         * its data member as the MyString reference appended to this' data
         * member.
         *
         * @param MyString& A reference to the MyString object that should be
         *                  concatenated with this
         *
         * @return MyString A new MyString object that has the concatenated
         *                  string as its data member
         */
        MyString operator+(const MyString&);
        /**
         * Pre-decrement operator overload. Will remove the last character from
         * the data member and return a reference to the class.
         *
         * @return MyString A reference to the modified class.
         */
        MyString operator--();
        /**
         * Post-decrement operator overload. Will remove the last character
         * from the data member and return a reference to the previous state of
         * the class before it was modified.
         *
         * @return MyString A reference to the previous, unmodified state of
         * the class.
         */
        MyString operator--(int);
        /**
         * Assignment operator overload. Will deep copy the members of the
         * right hand side of the operator to this.
         *
         * @param const MyString& A reference to the object to deep copy.
         *
         * @return MyString& A reference to this which should be modified.
         */
        MyString& operator=(const MyString&);
        /**
         * Sets the printAsUppercase static variable to the value of the passed
         * in parameter.
         *
         * @param bool The value to set printAsUppercase to
         *
         * @return void
         */
        static void setPrintAsUppercase(bool);
        /**
         * Attempts to emulate <cstring>'s strcmp() function. Will compare the
         * individual elements of the first argument to the second.
         *
         * @param const char* A character array to be compared
         * @param const char* Character array to be compared against.
         *
         * @return static int Will return -1, 0, or 1 depending on whether to
         *                    characters in the first argument are less than,
         *                    equal to, or greater than the second argument
         *                    characters respectively.
         */
        static int stringComp(const char*, const char*);
        /**
         * Will return the number of elements found until a null-termination
         * character is found. Will exclude the null-termination character in
         * its element count.
         *
         * @param char* The c-string to find the length of
         *
         * @return static int The number of elements before the
         *                    null-termination character.
         */
        static int stringLength(char*);
        /**
         * Equality operator overload. Compares the data of the first argument
         * object to the second.
         *
         * @param const MyString& Object on LHS of operator
         * @param const MyString& Object on RHS of operator
         *
         * @return bool Whether or not the data arrays of the objects contain
         *              the same characters in the same index.
         */
        friend bool operator==(const MyString&, const MyString&);
        /**
         * Greater than operator overload. Compares the data of the first
         * argument to the second.
         *
         * @param const MyString& Object on LHS of operator
         * @param const MyString& Object on RHS of operator
         *
         * @return bool Whether or not the LHS object has characters that are
         *              greater than the characters in the RHS object.
         */
        friend bool operator>(const MyString&, const MyString&);
        /**
         * Greater than operator overload. Compares the data of the first
         * argument to the second.
         *
         * @param const MyString& Object on LHS of operator
         * @param const MyString& Object on RHS of operator
         *
         * @return bool Whether or not the LHS object has characters that are
         *              less than the characters in the RHS object.
         */
        friend bool operator<(const MyString&, const MyString&);
        /**
         * ostream operator overload. Outputs the characters contained in the
         * data member followed by the length in parenthesis.
         *
         * @param ostream& An ostream type object reference
         * @param const MyString& A reference to a MyString object
         *
         * @output ostream& In the format of "data(length)"
         */
        friend ostream& operator <<(ostream&, const MyString&);
        /**
         * istream operator overload. Reads input from the istream object and
         * places it into the MyString data member. Will only accept a maximum
         * of 254 characters.
         *
         * @param istream& Reference to an istream object.
         * @param MyString& A reference to a MyString object to place the read
         *                  input to.
         */
        friend istream& operator >>(istream&, MyString&);
        /**
         * Manipulates the data member by bitwise ANDing each element by the
         * bitewise NOT of 0x20.
         */
        void uppercase();
        /**
         * Returns the length private member.
         *
         * @return int The length private member.
         */
        int getLength();
};
#endif
