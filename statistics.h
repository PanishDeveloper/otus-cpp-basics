#pragma once

#include <vector>
#include <string>

// Base interface for all statistical metrics
class IStatistics {
public:
    virtual ~IStatistics() = default;
    virtual void update(double next) = 0;
    [[nodiscard]]virtual double eval() const = 0;
    [[nodiscard]]virtual std::string name() const = 0;
};

// Calculates the minimum value from a sequance of numbers
class Min : public IStatistics {
public:
    Min();
    void update(double next) override;
    [[nodiscard]]double eval() const override;
    [[nodiscard]]std::string name() const override;

private:
    double min_value;
    int count;
};

// Calculates the maximum value from a sequance of numbers
class Max : public IStatistics {
public:
    Max();
    void update(double next) override;
    [[nodiscard]]double eval() const override;
    [[nodiscard]]std::string name() const override;

private:
    double max_value;
    int count;
};

// Calculates the arithmetic mean of a sequance of numbers
class Mean : public IStatistics {
public:
    Mean();
    void update(double next) override;
    [[nodiscard]]double eval() const override;
    [[nodiscard]]std::string name() const override;

private:
    double sum;
    int count;
};

// Calculates the standart deviation of a sequance of numbers
class StandardDeviation : public IStatistics {
public:
    StandardDeviation();
    void update(double next) override;
    [[nodiscard]]double eval() const override;
    [[nodiscard]]std::string name() const override;

private:
    double sum;
    double sum_squares;
    int count;
};

// Base class for percentile calculations
class PercentileBase : public IStatistics {
public:
    PercentileBase(double percentile, std::string name_str);
    void update(double next) override;
    [[nodiscard]]double eval() const override;
    [[nodiscard]]std::string name() const override;

protected:
    std::vector<double> values;
    double m_percentile;
    std::string m_name_str;
};

// Calculates the 90th percentile of a sequance of numbers
class Pct90 : public PercentileBase {
public:
    Pct90();
};

// Calculates the 95th percentile of a sequance of numbers
class Pct95 : public PercentileBase {
public:
    Pct95();
};