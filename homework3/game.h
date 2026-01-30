#pragma once

class Game {
private:
    int targetNumber = 0;
    int attempts = 0;
    int maxValue = 100;

public:
    // Game methods
    void setMaxValue(int maxVal);
    void startNewGame();
    bool makeGuess(int guess);
    [[nodiscard]]int getAttempts() const;
    [[nodiscard]]int getMaxValue() const;
};