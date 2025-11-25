#pragma once

#include <string>
using namespace std;

/**
 * Reads a string from std in.
 * @param prompt Text to show.
 * @return Read string
 */
string readString(const string& prompt) {
    string input;
    cout << prompt + ": ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

/**
 * Converts a string to lower case.
 * @param s String to transform.
 * @return Lower case string.
 */
static string toLowerString(string s) {
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return tolower(c); });
    return s;
}
