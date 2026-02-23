#include "statistics.h"

#include <limits>
#include <stdexcept>
#include <cmath>
#include <algorithm>

Min::Min() : min_value(std::numeric_limits<double>::infinity()), count(0) {}

void Min::update(double next)
{
    if (next < min_value) {
        min_value = next;
    }
    count++;
}

double Min::eval() const
{
    if (count == 0) {
        throw std::logic_error("No data for minimum calculation");
    }
    return min_value;
}

std::string Min::name() const { return "Min"; }


Max::Max() : max_value(-std::numeric_limits<double>::infinity()), count(0) {}

void Max::update(double next)
{
    if (next > max_value) {
        max_value = next;
    }
    count++;
}

double Max::eval() const
{
    if (count == 0) {
        throw std::logic_error("No data for maximum calculation");
    }
    return max_value;
}

std::string Max::name() const { return "Max"; }

Mean::Mean() : sum(0), count(0) {}

void Mean::update(double next)
{
    sum += next;
    count++;
}

double Mean::eval() const
{
    if (count == 0) {
        throw std::logic_error("No data for mean calculation");
    }
    return sum / count;
}

std::string Mean::name() const { return "Mean"; }


StandardDeviation::StandardDeviation() : sum(0.0), sum_squares(0.0), count(0) {}

void StandardDeviation::update(double next)
{
    sum += next;
    sum_squares += next * next;
    count++;
}

double StandardDeviation::eval() const
{
    if (count < 2) {
        throw std::logic_error("At least 2 values required for standard deviation");
    }

    double mean = sum / count;
    double variance = (sum_squares - sum * mean)/ count;

    if (variance < 0.0) { variance = 0.0; }

    return std::sqrt(variance);
}

std::string StandardDeviation::name() const { return "STD"; }


PercentileBase::PercentileBase(double percentile, std::string name_str)
    : m_percentile(percentile), m_name_str(std::move(name_str)) {}

void PercentileBase::update(double next)
{
    values.push_back(next);
}

double PercentileBase::eval() const
{
    if (values.empty())
    {
        throw std::logic_error("No data for percentile calculation");
    }

    std::vector<double> sorted = values;
    std::sort(sorted.begin(), sorted.end());

    auto index = static_cast<size_t>(sorted.size() * m_percentile);
    if (index >= sorted.size()) { index = sorted.size() - 1; }

    return sorted[index];
}

std::string PercentileBase::name() const { return m_name_str; }


Pct90::Pct90() : PercentileBase(0.90, "pct90") {}


Pct95::Pct95() : PercentileBase(0.95, "pct95") {}