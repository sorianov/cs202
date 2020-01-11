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
        MyString(); // done
        MyString(char*); //done
        MyString(MyString&); //done
        ~MyString(); //done
        void uppercase(); //done
        int getLength(); //done
        static void setPrintAsUppercase(bool); //done
        MyString operator+(const MyString&); //done?
        MyString operator--(); //done
        MyString operator--(int); //done
        MyString& operator=(const MyString&); //done
        static int stringComp(const char*, const char*); //done
        int stringLength(char*); //done
        friend bool operator==(const MyString&, const MyString&); //done
        friend bool operator>(const MyString&, const MyString&); //done
        friend bool operator<(const MyString&, const MyString&); //done
        friend ostream& operator <<(ostream&, const MyString&); //done
        friend istream& operator >>(istream&, MyString&);
};
#endif
