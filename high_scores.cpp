#include "high_scores.h"
#include <iostream>
#include <fstream>

using namespace std;

const string HIGH_SCORES_FILE = "high_scores.txt";
static vector<ScoreRecord> scores;

void HighScores::addScore(const string& name, int attempts) {
    scores.push_back({name, attempts});
    saveToFile();
}

vector<ScoreRecord> HighScores::getScores() {
    loadFromFile();
    return scores;
}

void HighScores::printScores() {
    loadFromFile();
    cout << "=== HIGH SCORES ===\n";
    for (const auto& record : scores) {
        cout << record.name << ":" << record.attempts << endl;
    }
}

void HighScores::saveToFile() {
    ofstream file(HIGH_SCORES_FILE);
    if (file.is_open()) {
        for (const auto& record : scores) {
            file << record.name << " " << record.attempts << endl;
        }
        file.close();
    }
}

void HighScores::loadFromFile() {
    scores.clear();
    ifstream file(HIGH_SCORES_FILE);
    if (file.is_open()) {
        string name;
        int attempts;
        while (file >> name >> attempts){
            scores.push_back({name, attempts});
        }
        file.close();
    }
}

void HighScores::clear() {
    scores.clear();
}