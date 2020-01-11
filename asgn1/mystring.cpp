#include "mystring.h"
#include <iostream>

using namespace std;

bool MyString::printAsUppercase = false;

MyString::MyString() {
    data = nullptr;
    length = 0;
    printAsUppercase = false;
}

MyString::MyString(char* name) {
    int length = stringLength(name);
    data = new char[length+1];
    for (int i = 0; i < length+1; ++i) {
        data[i] = name[i];
    }
    this->length = length;
    printAsUppercase = false;
}

MyString::MyString(MyString& m) {
    data = new char[m.length+1];
    length = m.length;
    printAsUppercase = m.printAsUppercase;
    for (int i = 0; i < length+1; ++i) {
        data[i] = m.data[i];
    }
}
MyString::~MyString() {
    if (data != nullptr) {
        delete [] data;
        data = nullptr;
    }
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
    int i = 0;
    for(; str[i] != '\0'; ++i) {
    }
    return i;
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
    for (int k = 0; k < mLength+1; ++k) {
        str[i] = m.data[k];
        ++i;
    }
    MyString combined(str);
    return combined;
}

MyString MyString::operator--() {
    length = length - 1;
    char* str = new char[length+1];
    for (int i = 0; i < length; ++i) {
        str[i] = data[i];
    }
    str[length] = '\0';
    delete [] data;
    data = str;
    return *this;
}

MyString MyString::operator--(int i) {
    MyString temp = *this;
    length = length - 1;
    char* str = new char[length+1];
    for (int i = 0; i < length; ++i) {
        str[i] = data[i];
    }
    str[length] = '\0';
    delete [] data;
    data = str;
    return temp;
}

MyString& MyString::operator=(const MyString& m) {
    if (data) {
        delete [] data;
        data = nullptr;
    }
    length = m.length;
    printAsUppercase = m.printAsUppercase;
    data = new char[length+1];
    for (int i = 0; i < length+1; ++i) {
        data[i] = m.data[i];
    }
    return *this;
}

ostream& operator<<(ostream& os, const MyString& str) {
    if (MyString::printAsUppercase) {
        char* upper = new char[str.length+1];
        for (int i = 0; i < str.length; ++i) {
            upper[i] = str.data[i] & ~0x20;
        }
        upper[str.length] = '\0';
        os << upper << "(" << str.length << ")";
        delete [] upper;
        return os;
    }

    os << str.data << "(" << str.length << ")";
    return os;
}

istream& operator >>(istream& is, MyString& str) {
    const unsigned int maxLength = 255;
    char* buffer = new char[maxLength];
    if (str.data) {
        delete [] str.data;
        str.data = nullptr;
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
        buffer[i] = m;
        ++i;
    }
    buffer[i] = '\0';
    str.data = new char[i+1];
    for (int k = 0; k < i+1; ++k) {
        str.data[k] = buffer[k];
    }
    str.length = i;

    return is;
}

bool operator==(const MyString& str1, const MyString& str2) {
    //TODO reimplement this using MyString::stringComp
    // is there anything to compare?
    if (!str1.data || !str1.data) {
        // if they're both nullptr, they're equal
        if (str1.data == nullptr && str2.data == nullptr) {
            return true;
        }
        return false;
    }

    // are they at least the same length?
    if (str1.length != str2.length) {
        return false;
    }

    for (int i = 0; i < str1.length; ++i) {
        if (str1.data[i] != str2.data[i]) {
            return false;
        }
    }
    return true;
}

int MyString::stringComp(const char* str1, const char* str2) {
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
    MyString* strings = new MyString[argc - 1];
    for (int i = 0; i < argc-1; ++i) {
        strings[i] = MyString(argv[i+1]);
    }
    for (int i = 0; i < argc-1; ++i) {
        cout << strings[i] << " ";
    }
    cout << endl;
    MyString first(strings[0]);
    MyString last(strings[argc - 2]);
    if (first < last) {
        //cout << "The first string (" << argv[1] << ") ";
        cout << "The first string (" << first << ") ";
        //cout << "is less than the last string (" << argv[argc - 1] << ").";
        cout << "is less than the last string (" << last << ").";
        cout << endl;
    } else if (first > last) {
        cout << "The first string (" << argv[1] << ") ";
        cout << "is greater than the last string (" << argv[argc - 1] << ").";
        cout << endl;
    } else if (first == last) {
        cout << "The first string (" << argv[1] << ") ";
        cout << "is equal to the last string (" << argv[argc - 1] << ").";
        cout << endl;
    }
    for (int i = 0; i < argc-1; ++i) {
        cout << --strings[i] << " ";
    }
    cout << endl;
    MyString combined;
    combined = strings[0]-- + --strings[argc - 2];
    cout << combined << endl;
    combined.uppercase();
    cout << combined << endl;
    MyString::setPrintAsUppercase(true);
    for (int i = 0; i < argc-1; ++i) {
        cout << strings[i] << " ";
    }
    cout << endl;

    cout << strings[0] << endl;
    cout << strings[argc - 2] << endl;

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
