#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

// Template class for doubly linked list
// Elements are not contiguous in memory
template <typename T>
class DoublyLinkedList
{
public:
    DoublyLinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}
    ~DoublyLinkedList() { clear(); }

    DoublyLinkedList(const DoublyLinkedList& other) : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        Node* current = other.m_head;
        while (current)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        swap(other);
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other)
    {
        if (this != &other)
        {
            DoublyLinkedList temp(other);
            swap(temp);
        }

        return *this;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept
    {
        if (this != &other)
        {
            swap(other);
        }

        return *this;
    }

    void swap(DoublyLinkedList& other) noexcept
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
    }

    // Method for getting the list type
    [[nodiscard]] std::string get_type() const { return "DoublyLinkedList"; }

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

    // PUSH_BACK METHOD. For r-value
    void push_back(T&& value)
    {
        Node* new_node = new Node(std::move(value));

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

    // PUSH_FRONT METHOD. Adds element to the beginning
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

    // PUSH_FRONT METHOD. For r-value
    void push_front(T&& value)
    {
        Node* new_node = new Node(std::move(value));

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

    // INSERT NETHOD. Inserts element at specified position
    void insert(size_t index, const T& value)
    {
        if (index > m_size)
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
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;

        ++m_size;
    }

    // INSERT NETHOD. For r-value
    void insert(size_t index, T&& value)
    {
        if (index > m_size)
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

        Node* new_node = new Node(std::move(value));
        new_node->next = current;
        new_node->prev = current->prev;
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
    [[nodiscard]] size_t size() const { return m_size; }

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
    [[nodiscard]] bool empty() const { return m_size == 0; }

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

private:
    // STRUCT NODE
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        explicit Node(T&& value) : data(std::move(value)), next(nullptr), prev(nullptr) {}
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size;
};