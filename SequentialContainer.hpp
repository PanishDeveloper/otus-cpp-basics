#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>

// Template class for sequential container.
// Stores elements contiguously in memory
template <typename T>
class SequentialContainer
{
public:
    SequentialContainer() : m_data(nullptr), m_size(0), m_capacity(0) {}

    // Constructor with initial capacility
    explicit SequentialContainer(size_t initial_capacity) : m_data(nullptr), m_size(0), m_capacity(0)
    {
        if (initial_capacity > 0)
            reserve(initial_capacity);
    }

    ~SequentialContainer() { delete[] m_data; }

    SequentialContainer(const SequentialContainer& other) : m_data(nullptr), m_size(0), m_capacity(0)
    {
        if (other.m_size > 0)
        {
            reserve(other.m_capacity);
            for (size_t i = 0; i < other.m_size; ++i)
                m_data[i] = other.m_data[i];
            m_size = other.m_size;
        }
    }

    // Move constructor
    SequentialContainer(SequentialContainer&& other) noexcept
                                            : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        std::cout << "[CONTAINER] Move constructor called\n";
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    SequentialContainer& operator=(const SequentialContainer& other)
    {
        if (this != &other)
        {
            SequentialContainer temp(other);
            swap(temp);
        }

        return *this;
    }

    // Move assignment operator
    SequentialContainer& operator=(SequentialContainer&& other) noexcept
    {
        std::cout << "[CONTAINER] Move assignment called\n";
        if (this != &other)
        {
            delete[] m_data;

            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    void swap(SequentialContainer& other) noexcept
    {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    // PUSH_BACK METHOD . Adds element to the end
    void push_back(const T& value)
    {
        if (m_size == m_capacity)
        {
            size_t new_capacity = calculate_growth(m_capacity);
            reserve(new_capacity);
        }
        m_data[m_size++] = value;
    }

    // PUSH_BACK METHOD. For r-value
    void push_back(T&& value)
    {
        if (m_size == m_capacity)
        {
            size_t new_capacity = calculate_growth(m_capacity);
            reserve(new_capacity);
        }
        m_data[m_size++] = std::move(value);
    }

    // ADDED: Calculate new capacity with growth factor
    [[nodiscard]] static size_t calculate_growth(size_t current_capacity) noexcept
    {
        if (current_capacity == 0)
            return 1;

        auto new_capacity = static_cast<size_t>(current_capacity * 1.5);

        return (new_capacity > current_capacity) ? new_capacity : current_capacity + 1;

    }

    // RESERVE METHOD. Allocates memory for future elements
    void reserve(size_t new_capacity)
    {
        if (new_capacity <= m_capacity) return;

        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < m_size; ++i)
        {
            new_data[i] = std::move(m_data[i]);
        }

        delete[] m_data;

        m_data = new_data;
        m_capacity = new_capacity;
    }

    // INSERT METHOD. Inserts element at specified position
    void insert(size_t index, const T& value)
    {
        if (index > m_size)
            throw std::out_of_range("Index out of range");

        if (m_size == m_capacity)
        {
            size_t new_capacity = calculate_growth(m_capacity);
            reserve(new_capacity);
        }

        for (size_t i = m_size; i > index; --i)
            m_data[i] = std::move(m_data[i - 1]);

        m_data[index] = value;
        ++m_size;
    }

    // INSERT METHOD. For r-value
    void insert(size_t index, T&& value)
    {
        if (index > m_size)
            throw std::out_of_range("Index out of range");

        if (m_size == m_capacity)
        {
            size_t new_capacity = calculate_growth(m_capacity);
            reserve(new_capacity);
        }

        for (size_t i = m_size; i > index; --i)
            m_data[i] = std::move(m_data[i - 1]);

        m_data[index] = std::move(value);
        ++m_size;
    }

    // ADDED: Method to reduce capacity to fit current size
    void shrink_to_fit()
    {
        if (m_size == m_capacity) return;

        if (m_size == 0)
        {
            clear();
            return;
        }

        // Create new array exactly for current size
        T* new_data = new T[m_size];
        for (size_t i = 0; i < m_size; ++i)
            new_data[i] = std::move(m_data[i]);

        delete[] m_data;
        m_data = new_data;
        m_capacity = m_size;
    }

    // ERASE METHOD. Removes element at specifies position
    void erase(size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        for (size_t i = index; i < m_size - 1; ++i)
            m_data[i] = std::move(m_data[i + 1]);

        --m_size;
    }

    // SIZE MEHOD. Returns current number of elements
    [[nodiscard]]size_t size() const { return m_size; }

    // CLEAR METHOD. Removes all elements
    void clear()
    {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    // EMPTY METHOD. Check if container is empty
    [[nodiscard]]bool empty() const { return m_size == 0; }

    // CAPACITY METHOD. Returns allocated memory size
    [[nodiscard]]size_t capacity() const { return m_capacity; }

    // ADDED: Method to show memory efficience
    [[nodiscard]]double load_factor() const { return m_capacity == 0 ? 1.0 : static_cast<double>(m_size) / m_capacity; }

    // INDEX OPERATOR. Access by index (non - const)
    T& operator[](size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    // Access by index (const version for reading)
    const T& operator[](size_t index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");
        return m_data[index];
    }

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;
};