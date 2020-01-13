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
        MyString operator--();
        MyString operator--(int);
        MyString& operator=(const MyString&);
        static void setPrintAsUppercase(bool);
        static int stringComp(const char*, const char*);
        static int stringLength(char*);
        friend bool operator==(const MyString&, const MyString&);
        friend bool operator>(const MyString&, const MyString&);
        friend bool operator<(const MyString&, const MyString&);
        friend ostream& operator <<(ostream&, const MyString&);
        friend istream& operator >>(istream&, MyString&);
        void uppercase();
        int getLength();
};
#endif
