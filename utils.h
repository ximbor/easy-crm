#pragma once

#include <regex>
#include <string>
#include <sstream>

using namespace std;

/**
 * Clear cin buffer.
 */
void clearBuffer(bool clearInput = false) {
    if (clearInput)
        cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Reads a string from std in.
 * @param prompt Text to show.
 * @return Read string
 */
string readString(const string& prompt) {
    string input;
    cout << prompt + ": ";
    cin >> input;
    clearBuffer();
    return input;
}

/**
 * Converts a string to lower case.
 * @param str String to transform.
 * @return Lower case string.
 */
static string toLowerString(string str) {
    transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c){ return tolower(c); });
    return str;
}

/**
 * Validates a date
 * @param dateStr Date to validate.
 * @return True if the date is valid; False otherwise.
 */
bool isValidDateFormat(const string& dateStr) {
    if (const regex date_regex("^([0-9]{2})/([0-9]{2})/([0-9]{4})$"); !regex_match(dateStr, date_regex)) {
        return false;
    }
    return true;
}

/**
 * Validates a number.
 * @param numStr Numeric string
 * @return True if the input string is a number; otherwise false.
 */
bool isValidNumericInput(const string& numStr) {
    stringstream ss(numStr);
    double value;
    if (ss >> value && ss.eof()) {
        return true;
    }
    return false;
}