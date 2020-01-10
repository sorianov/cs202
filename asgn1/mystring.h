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
        int strcmp(const char*, const char*);
    public:
        MyString(); // done
        MyString(char*); //done
        MyString(MyString&);
        ~MyString();
        void uppercase(); //done
        int getLength(); //done
        static void setPrintAsUppercase(bool); //done
        MyString operator+(const MyString&); //done?
        MyString operator--();
        MyString operator--(int);
        MyString& operator=(const MyString&);
        int stringLength(char*); //done
        friend bool operator==(const MyString&, const MyString&);
        friend bool operator>(const MyString&, const MyString&);
        friend bool operator<(const MyString&, const MyString&);
        friend ostream& operator <<(ostream&, const MyString&); //done
        friend istream& operator >>(istream&, MyString&);
};
#endif
