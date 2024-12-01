#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// unction to get a double-precision fp number
double extractNumeric(const string& str) {
    bool hasSign = false;
    bool hasDecimalPoint = false;
    bool hasDigits = false;
    size_t length = str.length();

    // empty string
    if (length == 0) {
        return -999999.99;
    }

    for (size_t i = 0; i < length; i++) {
        char ch = str[i];

        if (isdigit(ch)) {
            hasDigits = true; // needs at least one digit
        } else if ((ch == '+' || ch == '-') && i == 0) {
            if (hasSign) { // only sign
                return -999999.99;
            }
            hasSign = true;
        } else if (ch == '.' && !hasDecimalPoint) {
            hasDecimalPoint = true;
        } else {
            // invalid
            return -999999.99;
        }
    }

    // makes sure there is valid input
    if (!hasDigits) {
        return -999999.99;
    }

    double result = 0.0;
    double fractionPart = 0.1;
    bool isNegative = (str[0] == '-');
    bool isFraction = false;

    for (char ch : str) {
        if (ch == '+' || ch == '-') {
            continue; // skips
        } else if (ch == '.') {
            isFraction = true;
        } else if (isdigit(ch)) {
            if (!isFraction) {
                result = result * 10 + (ch - '0');
            } else {
                result += (ch - '0') * fractionPart;
                fractionPart *= 0.1;
            }
        }
    }

    return isNegative ? -result : result;
}

int main() {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}
