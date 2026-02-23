#include "statistics.h"
#include <iostream>
#include <memory>

int main()
{
    std::vector<std::unique_ptr<IStatistics>> statistics;

    statistics.emplace_back(std::make_unique<Min>());
    statistics.emplace_back(std::make_unique<Max>());
    statistics.emplace_back(std::make_unique<Mean>());
    statistics.emplace_back(std::make_unique<StandardDeviation>());
    statistics.emplace_back(std::make_unique<Pct90>());
    statistics.emplace_back(std::make_unique<Pct95>());

    std::cout << "Enter numbers (Ctrl+D to finnish):\n";

    double val;
    while (std::cin >> val)
    {
        for (const auto& stat : statistics) { stat->update(val); }
    }

    std::cout << std::endl;

    if (!std::cin.eof() && !std::cin.good())
    {
        std::cerr << "\nInvalid input.\n";
        return 1;
    }

    for (const auto& stat : statistics)
    {
        std::string stat_name = stat->name();
        try
        {
            double value = stat->eval();
            std::cout << stat_name << " = " << value << "\n";
        } catch (const std::logic_error&)
        {
            std::cout << stat_name << " = N/A\n";
        }
    }

    return 0;
}