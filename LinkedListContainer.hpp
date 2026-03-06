#pragma once

#include <iostream>
#include <stdexcept>

// Template class for doubly linked list
// Elements are not contiguous in memory
template <typename T>
class LinkedListContainer
{
public:
    LinkedListContainer() : m_head(nullptr), m_tail(nullptr), m_size(0) {}
    ~LinkedListContainer() { clear(); }

    LinkedListContainer(const LinkedListContainer&) = delete;
    LinkedListContainer& operator=(const LinkedListContainer&) = delete;

    // PUSH_BACK METHOD. Adds element to the end
    void push_back(const T& value)
    {
        Node* new_node = new Node(value);

        if (m_head == nullptr)
            m_head = m_tail = new_node;
        else
        {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }

        ++m_size;
    }

    // PUSH_FRONT METHOD. Adds element to the brginning
    void push_front(const T& value)
    {
        Node* new_node = new Node(value);

        if (m_head == nullptr)
            m_head = m_tail = new_node;
        else
        {
            new_node->next = m_head;
            m_head->prev = new_node;
            m_head = new_node;
        }

        ++m_size;
    }

    // INDEX OPERATOR. Access by index
    T& operator[](size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* current = m_head;
        for (size_t i = 0; i < index; ++i)
            current = current->next;

        return current->data;
    }

    // Const version
    const T& operator[](size_t index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* current = m_head;
        for (size_t i = 0; i < index; ++i)
            current = current->next;

        return current->data;
    }

    // INSERT NETHOD. Inserts element at specified position
    void insert(size_t index, const T& value)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        if (index == m_size)
        {
            push_back(value);
            return;
        }

        if (index == 0)
        {
            push_front(value);
            return;
        }

        Node* current = m_head;
        for (size_t i = 0; i < index - 1; ++i)
            current = current->next;

        Node* new_node = new Node(value);
        new_node->next = current;
        current->prev->next = new_node;
        current->prev = new_node;

        ++m_size;
    }

    // ERASE METHOD. Removes element at specified position
    void erase(size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* to_delete = m_head;
        for (size_t i = 0; i < index; ++i)
            to_delete = to_delete->next;

        // Redirect pointers
        if (to_delete->prev)
            to_delete->prev->next = to_delete->next;
        else
            m_head = to_delete->next;

        if (to_delete->next)
            to_delete->next->prev = to_delete->prev;
        else
            m_tail = to_delete->prev;

        delete to_delete;
        --m_size;
    }

    // SIZE METHOD.
    size_t size() const { return m_size; }

    // CLEAR METHOD.
    void clear()
    {
        Node* current = m_head;

        while (current)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    // EMPTY METHOD.
    bool empty() const { return m_size == 0; }

private:
    // STRUCT NODE
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* m_head;
    Node* m_tail;
    int m_size;
};