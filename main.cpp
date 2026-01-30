#include <iostream>
#include <limits>
#include "game.h"

using namespace std;

void PlayGame() {
    Game game;
    game.startNewGame();

    int num;
    bool guessed = false;

    cout << "Welcome to the 'Guess the number' game! ";
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
}

int main()
{
    int choice;
    do {
        cout << "\n===MENU===\n";
        cout << "1. New Game.\n";
        cout << "2. Exit.\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << endl;

        if (cin.fail()) {
            cout << "Invalid input! Please enter 1 or 2.\n\n";
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
                cout << "Thanks for playing! Goodbye!\n";
                break;
            default:
                cout << "Invalid input! Please enter 1 or 2.\n\n";
        }
    } while (choice != 2);
}