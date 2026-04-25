#pragma once

// Class with static counters to track constructor/destructor calls
class TestCounter
{
public:
    // Contructor with explicit to prevent implicit conversions
    explicit TestCounter(int value = 0) noexcept : _value(value) { _alive++; }

    // Copy constructor
    TestCounter(const TestCounter& other) noexcept : _value(other._value) { _alive++; }

    // Destructor
    ~TestCounter() noexcept { _destructor++; _alive--; }

    // Reset static counters (call in SetUp)
    static void reset_counts() noexcept
    {
        _alive = 0;
        _destructor = 0;
    }

    // Getters for tests
    [[nodiscard]] static int get_alive() noexcept { return _alive; }
    [[nodiscard]] static int get_destructor() noexcept { return _destructor; }

    [[nodiscard]] int get_value() const noexcept { return _value; }

private:
    static inline int _alive = 0;
    static inline int _destructor = 0;
    int _value;
};