#include <iostream>
#include <random>
#include "game.h"

using namespace std;

void Game::setMaxValue(int maxVal) {
    maxValue = maxVal;
}

void Game::startNewGame() {
    // Initializing the random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<>dis(1, maxValue);

    targetNumber = dis(gen);
    attempts = 0;
}

bool Game::makeGuess(int guess) {
    attempts++;

    if (guess < targetNumber) {
        cout << "The hidden number is bigger!\n";
        return false;
    }
    else if (guess > targetNumber) {
        cout << "The hidden number is smaller!\n";
        return false;
    }
    else {
        cout << "You guessed the number in " << attempts << " attempts!\n\n";
        return true;
    }
}

int Game::getAttempts() const {
    return attempts;
}

int Game::getMaxValue() const {
    return maxValue;
}