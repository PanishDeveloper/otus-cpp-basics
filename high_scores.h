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
    static std::map<std::string, int> getBestScores();
    static void printScores();
    static void saveToFile();
    static void loadFromFile();
    static void clear();
    static void ensureLoaded();

private:
    static std::vector<ScoreRecord> scores;
    static std::string HIGH_SCORES_FILE;
    static bool isLoaded;
};