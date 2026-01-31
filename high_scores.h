#pragma once

#include <string>
#include <vector>

struct ScoreRecord {
    std::string name;
    int attempts;
};

class HighScores {
public:
    static void addScore(const std::string& name, int attempts);
    static std::vector<ScoreRecord> getScores();
    static void printScores();
    static void saveToFile();
    static void loadFromFile();
    static void clear();
};