#pragma once

#include <iostream>
#include <stdexcept>

// Template class for sequential container.
// Stores elements contiguously in memory
template <typename T>
class SequentialContainer
{
public:
    SequentialContainer() : m_data(nullptr), m_size(0), m_capacity(0) {}
    ~SequentialContainer() { delete[] m_data; }

    SequentialContainer(const SequentialContainer&) = delete;
    SequentialContainer& operator=(const SequentialContainer&) = delete;

    // PUSH_BACK METHOD . Adds element to the end
    void push_back(const T& value)
    {
        if (m_size == m_capacity)
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        m_data[m_size++] = value;
    }

    // RESERVE METHOD. Allocates memory for future elements
    void reserve(size_t new_capacity)
    {
        if (new_capacity <= m_capacity) return;

        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < m_size; ++i)
        {
            new_data[i] = m_data[i];
        }

        delete[] m_data;

        m_data = new_data;
        m_capacity = new_capacity;
    }

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

    // INSERT METHOD. Inserts element at specified position
    void insert(size_t index, const T& value)
    {
        if (index > m_size)
            throw std::out_of_range("Index out of range");

        if (index == m_size)
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);

        for (size_t i = m_size; i > index; --i)
            m_data[i] = m_data[i - 1];

        m_data[index] = value;
        ++m_size;
    }

    // ERASE METHOD. Removes element at specifies position
    void erase(size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        for (size_t i = index; i < m_size - 1; ++i)
            m_data[i] = m_data[i + 1];

        --m_size;
    }

    // SIZE MEHOD. Returns current number of elements
    size_t size() const { return m_size; }

    // CLEAR METHOD. Removes all elements
    void clear()
    {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    // EMPTY METHOD. Check if container is empty
    bool empty() const { return m_size == 0; }

    // CAPACITY METHOD. Returns allocated memory size
    size_t capacity() const { return m_capacity; }

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;
};