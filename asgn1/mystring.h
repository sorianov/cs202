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
        MyString();
        MyString(char*);
        MyString(MyString&);
        ~MyString();
        void uppercase();
        int getLength();
        static void setPrintAsUppercase(bool);
        MyString operator+(const MyString&);
        MyString operator--();
        MyString operator--(int);
        MyString& operator=(const MyString&);
        friend bool operator==(const MyString&, const MyString&);
        friend bool operator>(const MyString&, const MyString&);
        friend bool operator<(const MyString&, const MyString&);
        friend ostream& operator <<(ostream&, const MyString&);
        friend istream& operator >>(istream&, MyString&);
};
#endif
