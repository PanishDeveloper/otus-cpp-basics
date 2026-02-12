#include "argument.h"
#include <iostream>
#include <string>

using namespace std;

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
            if (i + 1 < argc) {
                try {
                    result.maxValue = stoi(argv[i + 1]);
                    if (result.maxValue <= 0) {
                        result.error = true;
                        result.errorMessage = "Error: max value must be positive\n";
                        return result;
                    }
                    i++;
                } catch (const exception&) {
                    result.error = true;
                    result.errorMessage = "Error: invalid value for -max\n";
                    return result;
                }
            }
            else {
                result.error = true;
                result.errorMessage = "Error: -max requires a value\n";
                return result;
            }
        }
        else if (arg == "-level") {
            result.hasLevel = true;
            if (i + 1 < argc) {
                try {
                    result.level = stoi(argv[i + 1]);
                    if (result.level < 1 || result.level > 3) {
                        result.error = true;
                        result.errorMessage = "Error: level must be between 1 and 3\n";
                        return result;
                    }
                    i++;
                } catch (const exception&) {
                    result.error = true;
                    result.errorMessage = "Error: invalid value for -level\n";
                    return result;
                }
            }
            else {
                result.error = true;
                result.errorMessage = "Error: -level requires a value\n";
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