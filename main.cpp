#include "statistics.h"
#include <iostream>

int main()
{
    std::vector<IStatistics*> statistics = {
        new Min(),
        new Max(),
        new Mean(),
        new StandardDeviation(),
        new Pct90(),
        new Pct95()
    };

    std::cout << "Enter numbers (Ctrl+D to finnish):\n";

    double val;
    while (std::cin >> val)
    {
        for (auto* stat : statistics) { stat->update(val); }
    }

    std::cout << std::endl;

    if (!std::cin.eof() && !std::cin.good())
    {
        std::cerr << "\nInvalid input.\n";
        for (auto* stat : statistics) { delete stat; }
        return 1;
    }

    for (auto* stat : statistics)
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

    for (auto* stat : statistics) { delete stat; }

    return 0;
}