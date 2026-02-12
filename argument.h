#pragma once
#include <string>

struct ParsedArgs {
    int maxValue = 100;
    bool showTableOnly = false;
    bool hasMax = false;
    bool hasLevel = false;
    int level = 0;
    bool error = false;
    std::string errorMessage;
};
ParsedArgs ParseArguments(int argc, char* argv[]);
void PrintUsage();
bool ValidateArguments(const ParsedArgs& args, int& maxValue, bool& showTableOnly);