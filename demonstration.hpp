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

// Function for displaying the menu
inline void showMenu()
{
    std::cout << "\n============= CONTAINER DEMONSTRATION =============\n";
    std::cout << "=============           MENU          =============\n";
    std::cout << "1. Test Sequential Container (with capacity growth)\n";
    std::cout << "2. Test Doubly Linked List\n";
    std::cout << "3. Test Singly Linked List\n";
    std::cout << "4. Exit\n";
    std::cout << "===================================================\n";
    std::cout << "Enter your choice: ";
}