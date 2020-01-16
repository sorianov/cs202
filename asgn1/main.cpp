#include "mystring.h"

int main(int argc, char* argv[]) {
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

    stringsIter = strings;
    for (int i = 0; i < argc-1; ++i) {
        cout << *stringsIter << " ";
        ++stringsIter;
    }
    cout << endl;

    stringsIter = strings;
    MyString first(*stringsIter);
    MyString last(*lastString);
    if (first < last) {
        cout << "The first string (" << first << ") ";
        cout << "is less than the last string (" << last << ").";
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
    }
    cout << endl;
}
