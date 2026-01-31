#include <iostream>
#include <limits>
#include "game.h"
#include "high_scores.h"

using namespace std;

void PlayGame() {
    Game game;
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

int main()
{
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
                PlayGame();
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