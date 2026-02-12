#include "high_scores.h"
#include <iostream>
#include <fstream>

using namespace std;

string HighScores::HIGH_SCORES_FILE = "high_scores.txt";
vector<ScoreRecord> HighScores::scores;
bool HighScores::isLoaded = false;

void HighScores::addScore(const string& name, int attempts) {
    scores.push_back({name, attempts});
    saveToFile();
}

void HighScores::addOrUpdateScore(const string& name, int attempts) {
    ensureLoaded();
    bool updated = false;

    // We are looking for an existing record for this player
    for (auto& record : scores) {
        if (record.name == name) {
            if (attempts < record.attempts) {
                int oldRecord = record.attempts;
                record.attempts = attempts;
                cout << "Congratulations! You beat your previous record of " << oldRecord << " attempts.";
                cout << " The new record is " << record.attempts << " attempts.\n";
            }
            updated = true;
            break;
        }
    }

    // If there was no record, add a new one
    if (!updated) {
        scores.push_back({name, attempts});
    }
}

map<std::string, int> HighScores::getBestScores() {
    ensureLoaded();
    map <string, int> bestScores;

    for (const auto& record : scores) {
        // If the player is not in the map yer or his result is better (fewer attemps)
        if (bestScores.find(record.name) == bestScores.end() || record.attempts < bestScores[record.name]) {
            bestScores[record.name] = record.attempts;
        }
    }
    return bestScores;
}

void HighScores::printScores() {
    ensureLoaded();
    auto bestScores = getBestScores();

    if (bestScores.empty()) {
        cout << "=== HIGH SCORES ===\nNo scores yet. Be the first!\n";
        return;
    }

    vector<pair<string, int>> sortedScores(bestScores.begin(), bestScores.end());
    sort(sortedScores.begin(), sortedScores.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {return a.second < b.second;});

    cout << "=== HIGH SCORES ===\n";
    cout << "Player\t   Attempts\n===================\n";
    for (const auto& [name, attempts] : sortedScores) {
        cout << name << "\t\t" << attempts << endl;
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
    isLoaded = true;
}

void HighScores::ensureLoaded() {
    if (!isLoaded) {
        loadFromFile();
        isLoaded = true;
    }
}