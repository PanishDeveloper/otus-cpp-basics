#include "argument.h"
#include <iostream>
#include <string>

using namespace std;

bool ParseIntArgument(const string& currentArg, const string& nextArg, int& outValue,
                          int minValue, int maxValue, string& errorMessage) {
    if (nextArg.empty()) {
        errorMessage = "Error: " + currentArg + " requires a value\n";
        return false;
    }

    try {
        outValue = stoi(nextArg);
        if (outValue < minValue || outValue > maxValue) {
            errorMessage = "Error: " + currentArg + " value must be between " +
                          to_string(minValue) + " and " + to_string(maxValue) + "\n";
            return false;
        }
        return true;
    } catch (const exception&) {
        errorMessage = "Error: invalid value for " + currentArg + "\n";
        return false;
    }
}


// Prints the help message with program usage instructions
void PrintUsage() {
    cout << "Usage:\n guess_the_number[options]\n";
    cout << "Options:\n -max <value>   Set maximum number to guess (default 100)\n";
    cout << " -table         Show high scores and exit\n";
    cout << " -level <1|2|3> Set difficulty level (1:10, 2:50, 3:100)\n";
    cout << "                Note: -max and -level cannot be used together\n";
}

// A functions for parsing command line arguments
ParsedArgs ParseArguments(int argc, char* argv[]) {
    ParsedArgs result;

    if (argc == 1) {
        return result;
    }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-table") {
            result.showTableOnly = true;
        }
        else if (arg == "-max") {
            result.hasMax = true;

            string nextArg;
            if (i + 1 < argc) {
                nextArg = argv[i + 1];
            }

            if (ParseIntArgument(arg, nextArg, result.maxValue,
                1, 1000000, result.errorMessage)) {
                i++;
            } else {
                result.error = true;
                return result;
            }
        }
        else if (arg == "-level") {
            result.hasLevel = true;

            string nextArg;
            if (i + 1 < argc) {
                nextArg = argv[i + 1];
            }

            if (ParseIntArgument(arg, nextArg, result.level,
                1, 3, result.errorMessage)) {
                i++; // пропускаем значение аргумента
            } else {
                result.error = true;
                return result;
            }
        }
        else {
            result.error = true;
            result.errorMessage = "Error: unknown argument '" + arg + "'\n";
            return result;
        }
    }
    return result;
}

bool ValidateArguments(const ParsedArgs& args, int& maxValue, bool& showTableOnly) {
    if (args.error) {
        cout << args.errorMessage << endl;
        PrintUsage();
        return false;
    }

    // Checking for conflicts
    if (args.hasMax && args.hasLevel) {
        cout << "Error: -max and -level cannot be used together\n";
        PrintUsage();
        return false;
    }

    // Applying values
    maxValue = args.maxValue;
    showTableOnly = args.showTableOnly;

    // Applying the difficult level
    if (args.hasLevel) {
        switch (args.level) {
            case 1: maxValue = 10; break;
            case 2: maxValue = 50; break;
            case 3: maxValue = 100; break;
            default:
                cout << "Error: invalid level value\n";
            return false;
        }
    }

    return true;
}