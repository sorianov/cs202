#include "mystring.h"
#include <iostream>

using namespace std;

bool MyString::printAsUppercase = false;

MyString::MyString() {
    this->data = NULL;
    this->length = 0;
    this->printAsUppercase = false;
}

MyString::MyString(char* name) {
    int length = stringLength(name);
    this->data = new char[length];
    for (int i = 0; i < length; ++i) {
        this->data[i] = name[i];
    }
    this->length = length;
    this->printAsUppercase = false;
}

MyString::~MyString() {
    delete [] data;
    //this->data = NULL;
}

int MyString::getLength() {
    return length;
}

void MyString::uppercase() {
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] = data[i] & ~0x20;
        
    }
    return;
}

void MyString::setPrintAsUppercase(bool uppercase) {
    printAsUppercase = uppercase;
}

int MyString::stringLength(char* str) {
    int length = 0;
    for(int i = 0; str[i] != '\0'; ++i) {
        ++length;
    }
    return length;
}

MyString MyString::operator+(const MyString& m) {
    int mLength = this->stringLength(m.data);
    int totalLength = mLength + this->length;
    char* str = new char[totalLength];
    int i = 0;
    for (int j = 0; j < this->length; ++j) {
        str[i] = this->data[j];
        ++i;
    }
    for (int k = 0; k < mLength; ++k) {
        str[i] = m.data[k];
        ++i;
    }
    MyString combined(str);
    return combined;
}

MyString MyString::operator--() {
    int newLength = length - 1;
    char* str = new char[newLength];
    for (int i = 0; i < newLength; ++i) {
        str[i] = data[i];
    }
    MyString m(str);
    return m;
}

ostream& operator<<(ostream& os, const MyString& str) {
    if (MyString::printAsUppercase) {
        char* upper = new char[str.length];
        for (int i = 0; i < str.length; ++i) {
            upper[i] = str.data[i] & ~0x20;
        }
        os << upper << "(" << str.length << ")";
        return os;
    }
    
    os << str.data << "(" << str.length << ")";
    return os;
}

istream& operator >>(istream& is, MyString& str) {
    char name[4] = "foo";
    is >> name;
    str.data = name;
    str.length = 3;
    return is;
}

int main() {
    char foo[] = "foo";
    char bar[] = "bar";
    MyString m(foo);
    MyString n(bar);
    MyString s;
    //cout << "m length " << m.getLength() << endl;
    //cout << "n length " << n.getLength() << endl;
    cout << m << endl;
    m.setPrintAsUppercase(true);
    cout << m << endl;
    m.setPrintAsUppercase(false);
    cout << m << endl;
    cout << n << endl;
    cout << m + n << endl;
    cout << --m << endl;
    //cout << "Enter a string: ";
    //cin >> s;
    //cout << s << endl;
    return 0;
}
