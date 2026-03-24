#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

// Template class for singly linked list
// Elements are not contiguous in memory
template <typename T>
class SinglyLinkedList
{
private:
    // STRUCT NODE
    struct Node
    {
        T data;
        Node* next;

        explicit Node(const T& value) : data(value), next(nullptr) {}
        explicit Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };

    Node* m_head;
    size_t m_size;

public:
    SinglyLinkedList() : m_head(nullptr), m_size(0) {}
    ~SinglyLinkedList() { clear(); }

    SinglyLinkedList(const SinglyLinkedList& other) : m_head(nullptr), m_size(0)
    {
        Node* current = other.m_head;
        while (current)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    // Move constructor
    SinglyLinkedList(SinglyLinkedList&& other) noexcept : m_head(nullptr), m_size(0)
    {
        swap(other);
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other)
    {
        if (this != &other)
        {
            SinglyLinkedList temp(other);
            swap(temp);
        }

        return *this;
    }

    // Move assignment operator
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept
    {
        if (this != &other)
            swap(other);

        return *this;
    }

    void swap(SinglyLinkedList& other) noexcept
    {
        std::swap(m_head, other.m_head);
        std::swap(m_size, other.m_size);
    }

    // Method for getting the list type
    [[nodiscard]] std::string get_type() const { return "SinglyLinkedList"; }

    // PUSH_BACK METHOD. Adds element to the end O(n)
    void push_back(const T& value)
    {
        Node* new_node = new Node(value);

        if (m_head == nullptr)
            m_head = new_node;
        else
        {
           Node* current = m_head;
            while (current->next != nullptr) { current = current->next; }

            current->next = new_node;
        }

        ++m_size;
    }

    // PUSH_BACK METHOD. For r-value
    void push_back(T&& value)
    {
        Node* new_node = new Node(std::move(value));

        if (m_head == nullptr)
            m_head = new_node;
        else
        {
            Node* current = m_head;
            while (current->next != nullptr) { current = current->next; }

            current->next = new_node;
        }

        ++m_size;
    }

    // PUSH_FRONT METHOD. Adds element to the beginning O(1)
    void push_front(const T& value)
    {
        Node* new_node = new Node(value);
        new_node->next = m_head;
        m_head = new_node;

        ++m_size;
    }

    // PUSH_FRONT METHOD. For r-value
    void push_front(T&& value)
    {
        Node* new_node = new Node(std::move(value));
        new_node->next = m_head;
        m_head = new_node;

        ++m_size;
    }

    // INSERT METHOD. Inserts element at specified position
    void insert(size_t index, const T& value)
    {
        if (index > m_size)
            throw std::out_of_range("Index out of range");

        if (index == 0)
        {
            push_front(value);
            return;
        }

        Node* current = m_head;
        for (size_t i = 0; i < index - 1; ++i)
            current = current->next;

        Node* new_node = new Node(value);
        new_node->next = current->next;
        current->next = new_node;

        ++m_size;
    }

    // INSERT NETHOD. For r-value
    void insert(size_t index, T&& value)
    {
        if (index > m_size)
            throw std::out_of_range("Index out of range");

        if (index == 0)
        {
            push_front(value);
            return;
        }

        Node* current = m_head;
        for (size_t i = 0; i < index - 1; ++i)
            current = current->next;

        Node* new_node = new Node(std::move(value));
        new_node->next = current->next;
        current->next = new_node;

        ++m_size;
    }

    // ERASE METHOD. Removes element at specified position
    void erase(size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        if (index == 0)
        {
            Node* to_delete = m_head;
            m_head = m_head->next;
            delete to_delete;
        }
        else
        {
            Node* current = m_head;
            for (size_t i = 0; i < index - 1; ++i)
                current = current->next;

            Node* to_delete = current->next;
            current->next = to_delete->next;
            delete to_delete;
        }

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
        m_size = 0;
    }

    // EMPTY METHOD.
    [[nodiscard]]bool empty() const { return m_size == 0; }

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

    // ITERATORS
    class iterator
    {
    private:
        Node* m_node;

    public:
        iterator() : m_node(nullptr) {}
        explicit iterator(Node* node) : m_node(node) {}

        // operator*() - dereference operator
        T& operator*() { return m_node->data; }
        const T& operator*() const { return m_node->data; }

        // get() - method to get value
        T& get() { return m_node->data; }
        const T& get() const { return m_node->data; }

        iterator& operator++() { m_node = m_node->next; return *this; }
        iterator operator++(int) { iterator tmp = *this; m_node = m_node->next; return tmp; }

        bool operator==(const iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const iterator& other) const { return m_node != other.m_node; }
    };

    iterator begin() { return iterator(m_head); }
    iterator end() { return iterator(nullptr); }
};