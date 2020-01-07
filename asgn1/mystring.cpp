#include "mystring.h"
#include <iostream>

using namespace std;

bool MyString::printAsUppercase;

MyString::MyString() {
    this->data = NULL;
    this->length = 0;
    this->printAsUppercase = false;
}

MyString::MyString(char* name) {
    int l = 0;
    for (int i = 0; name[i] != '\0'; ++i) {
        ++l;
    }
    this->data = new char[l];
    for (int i = 0; name[i] != '\0'; ++i) {
        this->data[i] = name[i];
    }
    this->length = this->getLength();
    this->printAsUppercase = false;
}

MyString::~MyString() {
    //if (this->data) {
        //delete [] this->data;
    //}
    this->data = NULL;
}

int MyString::getLength() {
    int i = 0;
    if (data) {
        while(data[i]) {
            i++;
        }
    }
    
    return i;
}

void MyString::uppercase() {
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] = data[i] & ~0x20;
        
    }
    return;
}

ostream& operator<<(ostream& os, const MyString& str) {
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
    char foo[] = "foobar";
    char bar[] = "bar";
    MyString m(bar);
    MyString n(foo);
    MyString s;
    cout << "m length " << m.getLength() << endl;
    cout << "n length " << n.getLength() << endl;
    n.uppercase();
    cout << "n length " << n.getLength() << endl;
    cout << m << endl;
    cout << n << endl;
    cout << "Enter a string: ";
    cin >> s;
    //cout << s << endl;
    return 0;
}
