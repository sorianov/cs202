#include "mystring.h"
#include <iostream>

using namespace std;

bool MyString::printAsUppercase = false;

MyString::MyString() {
    data = NULL;
    length = 0;
}

MyString::MyString(char* name) {
    int length = MyString::stringLength(name);
    data = new char[length];
    char* str = data;
    for (int i = 0; i < length; ++i) {
        *str = *name;
        ++str;
        ++name;
    }
    this->length = length;
}

MyString::MyString(MyString& m) {
    data = new char[m.length];
    length = m.length;
    char* str1 = data;
    char* str2 = m.data;
    for (int i = 0; i < length; ++i) {
        *str1 = *str2;
        ++str1;
        ++str2;
    }
}

MyString::~MyString() {
    if (data) {
        delete [] data;
        data = NULL;
    }
}

int MyString::getLength() {
    return length;
}

void MyString::uppercase() {
    char* str = data;
    for (int i = 0; i < length; ++i) {
        *str = *str & ~0x20;
        ++str;
    }
    return;
}

void MyString::setPrintAsUppercase(bool uppercase) {
    printAsUppercase = uppercase;
}

int MyString::stringLength(char* str) {
    int i = 0;
    for(; *str != '\0'; ++i) {
        ++str;
    }
    return i;
}

MyString MyString::operator+(const MyString& m) {
    int totalLength = m.length + this->length;
    char* str = new char[totalLength];
    char* strIter = str;
    char* dataIter = data;
    for (int j = 0; j < this->length; ++j) {
        *strIter = *dataIter;
        ++strIter;
        ++dataIter;
    }
    
    dataIter = m.data;
    for (int k = 0; k < m.length; ++k) {
        *strIter = *dataIter;
        ++strIter;
        ++dataIter;
    }
    
    MyString combined(str);
    return combined;
}

MyString MyString::operator--() {
    if (length == 0) {
        return *this;
    }
    length = length - 1;
    char* str = new char[length];
    char* dataIter = data;
    char* strIter = str;
    for (int i = 0; i < length; ++i) {
        *strIter = *dataIter;
        ++strIter;
        ++dataIter;
    }
    delete [] data;
    data = str;
    return *this;
}

MyString MyString::operator--(int i) {
    if (length == 0) {
        return *this;
    }
    MyString temp = *this;
    length = length - 1;
    char* str = new char[length];
    char* strIter = str;
    char* dataIter = data;
    for (int i = 0; i < length; ++i) {
        *strIter = *dataIter;
        ++strIter;
        ++dataIter;
    }
    delete [] data;
    data = str;
    return temp;
}

MyString& MyString::operator=(const MyString& m) {
    if (data) {
        delete [] data;
        data = NULL;
    }
    length = m.length;
    printAsUppercase = m.printAsUppercase;
    data = new char[length];
    char* dataIter1 = data;
    char* dataIter2 = m.data;
    for (int i = 0; i < length; ++i) {
        *dataIter1 = *dataIter2;
        ++dataIter1;
        ++dataIter2;
        //data[i] = m.data[i];
    }
    return *this;
}

ostream& operator<<(ostream& os, const MyString& str) {
    char* dataIter = str.data;
    if (MyString::printAsUppercase) {
        char upper;
        for (int i = 0; i < str.length; ++i) {
            //upper[i] = str.data[i] & ~0x20;
            upper = *dataIter & ~0x20;
            ++dataIter;
            os << upper;
        }
        //os << upper << "(" << str.length << ")";
        os << "(" << str.length << ")";
        return os;
    }

    for (int i = 0; i < str.length; ++i) {
        os << *dataIter;
        ++dataIter;
    }
    //os << str.data << "(" << str.length << ")";
    os << "(" << str.length << ")";
    return os;
}

istream& operator>>(istream& is, MyString& str) {
    const unsigned int maxLength = 255;
    char* buffer = new char[maxLength];
    char* bufIter = buffer;
    if (str.data) {
        delete [] str.data;
        str.data = NULL;
        str.length = 0;
    }
    char m;
    int i = 0;
    while(is.get(m)) {
        if (i == (maxLength - 1)) {
            break;
        }
        if (m == '\n') {
            break;
        }
        *bufIter = m;
        ++bufIter;
        ++i;
    }
    str.data = new char[i];
    char* dataIter = str.data;
    bufIter = buffer;
    for (int k = 0; k < i; ++k) {
        *dataIter = *bufIter;
        ++dataIter;
        ++bufIter;
        //str.data[k] = buffer[k];
    }
    str.length = i;

    return is;
}

bool operator==(const MyString& str1, const MyString& str2) {
    //TODO reimplement this using MyString::stringComp
    // is there anything to compare?
    if (!str1.data || !str1.data) {
        // if they're both NULL, they're equal
        if (str1.data == NULL && str2.data == NULL) {
            return true;
        }
        return false;
    }

    // are they at least the same length?
    if (str1.length != str2.length) {
        return false;
    }

    char* dataIter1 = str1.data;
    char* dataIter2 = str2.data;
    for (int i = 0; i < str1.length; ++i) {
        if (*dataIter1 != *dataIter2) {
            return false;
        }
        ++dataIter1;
        ++dataIter2;
    }
    return true;
}

int MyString::stringComp(const char* str1, const char* str2) {
    //TODO don't use null terminated strings, add length params.
    // compares c1 to c2
    char c1 = *str1;
    char c2 = *str2;
    while (c1 != '\0') {
        //cout << "Comparing " << c1 << " " << c2 << endl;
        if (c2 == '\0') {
            return 1;
        }

        if (c1 < c2) {
            return -1;
        }

        if (c1 > c2) {
            return 1;
        }

        ++str1;
        ++str2;
        c1 = *str1;
        c2 = *str2;
    }

    if (c2 != '\0') {
        return -1;
    }

    return 0;
}

bool operator>(const MyString& str1, const MyString& str2) {
    return MyString::stringComp(str1.data, str2.data) > 0;
}

bool operator<(const MyString& str1, const MyString& str2) {
    return MyString::stringComp(str1.data, str2.data) < 0;
}

int main(int argc, char* argv[]) {
    /*
    for (int i = 1; i < argc; ++i) {
        cout << argv[i] << endl;
    }
    */
    if (argc < 2) {
        return 0;
    }
    MyString* strings = new MyString[argc - 1];
    MyString* stringsIter = strings;
    MyString* lastString;
    for (int i = 0; i < argc-1; ++i) {
        *stringsIter = MyString(argv[i+1]);
        ++stringsIter;
        if (i == (argc-3)) {
            lastString = stringsIter;
        }
    }
    cout << "lastString: " << *lastString << endl;
    stringsIter = strings;
    for (int i = 0; i < argc-1; ++i) {
        cout << *stringsIter << " ";
        //cout << strings[i] << " ";
        ++stringsIter;
    }
    cout << endl;
    stringsIter = strings;
    //MyString first(strings[0]);
    //MyString last(strings[argc - 2]);
    MyString first(*stringsIter);
    MyString last(*lastString);
    if (first < last) {
        cout << "The first string (" << first << ") ";
        //cout << "The first string (" << first << ") ";
        cout << "is less than the last string (" << last << ").";
        //cout << "is less than the last string (" << last << ").";
        cout << endl;
    } else if (first > last) {
        cout << "The first string (" << first << ") ";
        cout << "is greater than the last string (" << last << ").";
        cout << endl;
    } else if (first == last) {
        cout << "The first string (" << first << ") ";
        cout << "is equal to the last string (" << last << ").";
        cout << endl;
    }
    for (int i = 0; i < argc-1; ++i) {
        cout << --(*stringsIter) << " ";
        ++stringsIter;
        //cout << --strings[i] << " ";
    }
    cout << endl;
    MyString combined;
    stringsIter = strings;
    combined = (*stringsIter)-- + --(*lastString);
    cout << combined << endl;
    combined.uppercase();
    cout << combined << endl;
    MyString::setPrintAsUppercase(true);
    stringsIter = strings;
    for (int i = 0; i < argc-1; ++i) {
        cout << *stringsIter << " ";
        ++stringsIter;
        //cout << strings[i] << " ";
    }
    cout << endl;

    //cout << strings[0] << endl;
    //cout << strings[argc - 2] << endl;

    /*
    char foo[] = "foo";
    char bar[] = "bar";
    MyString m(foo);
    MyString n(bar);
    MyString l(m);
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

    if (n == m) {
        cout << "Strings are equal" << endl;
    }

    if (!(n == m)) {
        cout << "Strings aren't equal" << endl;
    }

    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    cout << "l: " << l << endl;
    l = n;
    cout << "l: " << l << endl;
    cout << "m: " << m-- << endl;
    if (n > m) {
        cout << "n is greater than m" << endl;
    } else {
        cout << "m is greater than n" << endl;
    }

    if (n < m) {
        cout << "n is less than m" << endl;
    } else {
        cout << "m is less than n" << endl;
    }
    cout << "m: " << m << endl;
    cin >> l;
    cout << l << endl;

    //cout << "Enter a string: ";
    //cin >> s;
    //cout << s << endl;
    return 0;
    */

}
