#pragma once

#include <string>
#include <vector>
#include <map>

struct ScoreRecord {
    std::string name;
    int attempts;
};

class HighScores {
public:
    static void addScore(const std::string& name, int attempts);
    static void addOrUpdateScore(const std::string& name, int attempts);
    static std::map<std::string, int> getBetScores();
    static void printScores();
    static void saveToFile();
    static void loadFromFile();
    static void clear();

private:
    static std::vector<ScoreRecord> scores;
    static std::string HIGH_SCORES_FILE;
};