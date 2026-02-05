#include <iostream>
#include <limits>
#include <string>
#include "game.h"
#include "high_scores.h"

using namespace std;

// Prints the help message with program usage instructions
void PrintUsage() {
    cout << "Usage:\n guess_the_number[options]\n";
    cout << "Options:\n -max <value> Set maximum number to guess (default 100)\n";
    cout << " -table                 Show high scores and exit\n";
}

// A functions for parsing command line arguments
bool ParseArguments(int argc, char* argv[], int& maxValue, bool& showTableOnly) {
    // Default value
    maxValue = 100;
    showTableOnly = false;

    if (argc == 1) {
        return true;
    }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-table") {
            showTableOnly = true;
        }
        else if (arg == "-max") {
            if (i + 1 < argc) {
                try {
                    maxValue = stoi(argv[i + 1]);
                    if (maxValue <= 0) {
                        cout << "Error: max value must be positive\n";
                        return false;
                    }
                    i++;
                } catch (const exception&) {
                    cout << "Error: invalid value for -max\n";
                    return false;
                }
            }
            else {
                cout << "Error: -max requires a value\n";
                return false;
            }
        }
        else {
            cout << "Error: unknown argument '" << arg << "'\n";
            PrintUsage();
            return false;
        }
    }
    return true;
}

void PlayGame(int maxValue) {
    Game game;
    game.setMaxValue(maxValue);
    game.startNewGame();

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    int num;
    bool guessed = false;

    cout << playerName << ", welcome to the 'Guess the number' game! ";
    cout << "I'm thinking of a number between 1 and " << game.getMaxValue() << ".\n";

    while (!guessed) {
        cout << "\nEnter a number from 1 and to " << game.getMaxValue() << ": ";
        cin >> num;

        // Checking the correctness of the input
        if (cin.fail()) {
            cout << "You didn't enter a number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (num < 1 || num > game.getMaxValue()) {
            cout << "Please enter a number between 1 and " << game.getMaxValue() << "!\n";
            continue;
        }
        guessed = game.makeGuess(num);
    }

    // Saving the result
    HighScores::addScore(playerName, game.getAttempts());
    // Showing the high score table
    HighScores::printScores();
}

int main(int argc, char* argv[]) {
    int maxValue;
    bool showTableOnly;

    if (!ParseArguments(argc, argv, maxValue, showTableOnly)) {
        return 1;
    }

    if (showTableOnly) {
        HighScores::printScores();
        return 0;
    }

    int choice;
    do {
        cout << "\n===MENU===\n";
        cout << "1. New Game.\n";
        cout << "2. View High Scores.\n";
        cout << "3. Exit.\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << endl;

        if (cin.fail()) {
            cout << "Invalid input! Please enter 1, 2 or 3.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                PlayGame(maxValue);
                break;
        case 2:
                HighScores::printScores();
                break;
            case 3:
                cout << "Thanks for playing! Goodbye!\n";
                break;
            default:
                cout << "Invalid input! Please enter 1, 2 or 3.\n\n";
        }
    } while (choice != 3);
}