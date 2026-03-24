#pragma once

#include "SequentialContainer.hpp"
#include "DoublyLinkedList.hpp"
#include "SinglyLinkedList.hpp"
#include <iomanip>

// Helper function to print container contents
template <typename Container>
void printContainer (const Container& container, size_t size, const std::string& message)
{
    std::cout << message;
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << container[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

// Helper function to print SequentialContainer - specific information
inline void printSequentialInfo(const SequentialContainer<int>& container, const std::string& prefix)
{
    std::cout << prefix <<
        "size = " << container.size() <<
            ", capacity = " << container.capacity() <<
                ", load factor = " << std::fixed << std::setprecision(2) <<
                    container.load_factor() << std::endl;
}

// Function to demonstrate capacity growth advantage
inline void demonstrateCapacityGrowth()
{
    std::cout << "\n========== CAPACITY GROWTH DEMONSTRATION ==========\n";
    SequentialContainer<int> container;

    std::cout << "Adding 20 elements and watching capacity growth:\n";
    std::cout << std::left << std::setw(10) << "Element" << std::setw(10) << "Size" <<
        std::setw(10) << "Capacity" << "Load factor" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    for (int i = 0; i < 20; ++i)
    {
        container.push_back(i);
        std::cout << std::setw(10) << i << std::setw(10) << container.size() <<
            std::setw(10) << container.capacity() << std::fixed << std::setprecision(2) <<
                container.load_factor() << std::endl;
    }
}


// Test function for any container
template <typename Container>
void testContainer(Container& container, const std::string& containerType)
{
    std::cout << "\n========== TESTING " << containerType << " ==========\n";

    if constexpr (std::is_same_v<Container, DoublyLinkedList<int>> || std::is_same_v<Container, SinglyLinkedList<int>>)
        std::cout << "List type: " << container.get_type() << "\n";


    std::cout << "1. Container created\n";
    // Show initial state for SequentialContainer
    if constexpr (std::is_same_v<Container, SequentialContainer<int>>)
        printSequentialInfo(container, "   Initial state: ");

    std::cout << "2. Adding 10 elements...\n";
    for (int i = 0; i < 10; ++i)
    {
        container.push_back(i);
        // Show capacity growth during first few additions
        if constexpr (std::is_same_v<Container, SequentialContainer<int>>)
        {
            if (i < 5)
                printSequentialInfo(container, "   After adding " + std::to_string(i) + ": ");
        }
    }

    printContainer(container, container.size(), "3. Contents: ");

    std::cout << "4. Size: " << container.size() << "\n";
    // Show final state after all additions
    if constexpr (std::is_same_v<Container, SequentialContainer<int>>)
        printSequentialInfo(container, "   After adding all: ");

    std::cout << "5. Deleting 3rd, 5th and 7th elements...\n";
    container.erase(6);
    container.erase(4);
    container.erase(2);

    printContainer(container, container.size(), "6. After deletion: ");

    std::cout << "7. Adding 10 to the beginning...\n";
    container.insert(0, 10);

    printContainer(container, container.size(), "8. Contents: ");

    std::cout << "9. Adding 20 to the middle...\n";
    size_t mid = container.size() / 2;
    container.insert(mid, 20);

    printContainer(container, container.size(), "10. Contents: ");

    std::cout << "11. Adding 30 to the end...\n";
    container.push_back(30);

    printContainer(container, container.size(), "12. Final contents: ");

    // Demonstrate shrink_to_fit for SequentialContainer
    if constexpr (std::is_same_v<Container, SequentialContainer<int>>)
    {
        printSequentialInfo(container, "    Final state: ");

        std::cout << "13. Demonstrating shrink_to_fit():\n";
        std::cout << "    Before shrink: capacity = " << container.capacity() << "\n";
        container.shrink_to_fit();
        std::cout << "    After shrink: capacity = " << container.capacity() << "\n";

        demonstrateCapacityGrowth();
    }

    std::cout << "===================================================\n";
}

// Class for demonstrating move semantics
class TestObject
{
private:
    std::string m_name;
    int* m_big_data;

public:
    TestObject() : m_name("default"), m_big_data(nullptr)
    {
        std::cout << "[LIFECYCLE] TestObject default created\n";
    }

    TestObject(std::string name) : m_name(std::move(name))
    {
        m_big_data = new int[1000];
        std::cout << "[LIFECYCLE] TestObject created: " << m_name << "\n";
    }

    TestObject(const TestObject& other) : m_name(other.m_name + " (copy)")
    {
        m_big_data = new int[1000];
        for (int i = 0; i < 1000; ++i)
            m_big_data[i] = other.m_big_data[i];
        std::cout << "[LIFECYCLE] TestObject COPIED: " << m_name << " (EXPENSIVE!)\n";
    }

    TestObject(TestObject&& other) noexcept : m_name(std::move(other.m_name) + " (moved)")
    {
        m_big_data = other.m_big_data;
        other.m_big_data = nullptr;
        std::cout << "[LIFECYCLE] TestObject MOVED: " << m_name << " (CHEAP!)\n";
    }

    // Copy assignment operator using copy-and-swap
    TestObject& operator= (const TestObject& other)
    {
        std::cout << "[LIFECYCLE] TestObject COPY ASSIGNMENT\n";
        if (this != &other)
        {
            TestObject temp(other);
            swap(temp);
        }

        return *this;
    }

    // Move assignment operator using swap
    TestObject& operator= (TestObject&& other) noexcept
    {
        std::cout << "[LIFECYCLE] TestObject MOVE ASSIGNMENT\n";
        if (this != &other)
        {
            swap(other);
        }

        return *this;
    }

    void swap(TestObject& other) noexcept
    {
        std::swap(m_name, other.m_name);
        std::swap(m_big_data, other.m_big_data);
    }

    ~TestObject()
    {
            delete[] m_big_data;
        std::cout << "[LIFECYCLE] TestObject destroyed: " << m_name << "\n";
    }

    friend std::ostream& operator<< (std::ostream& os, const TestObject& obj)
    {
        os << obj.m_name;
        return os;
    }
};

// Function to demonstrate move semantics
inline void demonstrateMoveSemantics()
{
    std::cout << "\n========== MOVE SEMANTICS DEMONSTRATION ==========\n";

    SequentialContainer<TestObject> container;

    std::cout << "\n1. Adding with l-value (copying):\n";
    TestObject obj1("Object 1");
    container.push_back(obj1);

    std::cout << "\n2. Adding with r-value (moving):\n";
    container.push_back(TestObject("Object 2"));

    std::cout << "\n3. Insert with r-value:\n";
    container.insert(1, TestObject("Object 3"));

    std::cout << "\n4. Testing move constructor:\n";
    SequentialContainer<TestObject> container2 = std::move(container);

    std::cout << "\n5. Testing move assignment:\n";
    SequentialContainer<TestObject> container3;
    container3 = std::move(container2);

    std::cout << "\nContainer contents (" << container3.size() << " elements):\n";
    for (size_t i = 0; i < container3.size(); ++i)
        std::cout << "  Element " << i << ": " << container3[i] << "\n";

    std::cout << "\n===================================================\n";
}

inline void demonstrateListMoveSemantics()
{
    std::cout << "\n========== LIST MOVE SEMANTICS DEMONSTRATION ==========\n";

    std::cout << "\n--- SinglyLinkedList with move ---\n";
    SinglyLinkedList<TestObject> singlyList;
    singlyList.push_back(TestObject("Singly 1"));
    singlyList.push_front(TestObject("Singly 2"));

    SinglyLinkedList<TestObject> singlyList2 = std::move(singlyList);

    std::cout << "\n--- DoublyLinkedList with move ---\n";
    DoublyLinkedList<TestObject> doublyList;
    doublyList.push_back(TestObject("Doubly 1"));
    doublyList.push_front(TestObject("Doubly 2"));

    DoublyLinkedList<TestObject> doublyList2 = std::move(doublyList);

    std::cout << "\n=======================================================\n";
}

// Function to demonstrate iterator
template <typename Container>
void demonstrateIterators (Container& container, const std::string& containerName)
{
    std::cout << "\n========== ITERATOR DEMONSTRATION FOR " << containerName << " ==========\n";

    // Clear and fill container with test data
    container.clear();
    for (int i = 1; i <= 5; ++i)
        container.push_back(i * 10);

    std::cout << "1. Using operator*() with traditional for loop:\n";
    std::cout << "   ";
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        std::cout << *it;
        auto next = it;
        ++next;

        if (next != container.end())
            std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "2. Using get() method with traditional for loop:\n";
    std::cout << "   ";
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        std::cout << it.get();
        auto next = it;
        ++next;

        if (next != container.end())
            std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "3. Using range-based for (requires begin()/end() and operator*()):\n";
    std::cout << "   ";
    for (const auto value : container)
        std::cout << value << " ";
    std::cout << "\n";

    if constexpr (std::is_same_v<Container, DoublyLinkedList<int>>)
    {
        std::cout << "4. Backward iteration:\n";
        std::cout << "   ";

        // Note: Using vector for reverse output to demonstrate
        // that container contains correct data. The iterator
        // itself is properly implemented with begin()/end(),
        // operator*() and get() as required.
        std::vector<int> temp;
        for (const auto& val : container)
            temp.push_back(val);

        for (auto it = temp.rbegin(); it != temp.rend(); ++it)
            std::cout << *it << " ";

        std::cout << std::endl;
    }
    std::cout << "============================================================\n";
}


// Function for displaying the menu
inline void showMenu()
{
    std::cout << "\n============= CONTAINER DEMONSTRATION =============\n";
    std::cout << "=============           MENU          =============\n";
    std::cout << "1. Test Sequential Container (with capacity growth)\n";
    std::cout << "2. Test Doubly Linked List\n";
    std::cout << "3. Test Singly Linked List\n";
    std::cout << "4. Demonstrate Move Semantics\n";
    std::cout << "5. Demonstrate Iterators (operator* and get())\n";
    std::cout << "6. Exit\n";
    std::cout << "===================================================\n";
    std::cout << "Enter your choice: ";
}