#include "SequentialContainer.hpp"
#include "LinkedListContainer.hpp"

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

// Test function for any container
template <typename Container>
void testContainer(Container& container, const std::string& containerType)
{
    std::cout << "\n========== TESTING " << containerType << " ==========\n";

    std::cout << "1. Container created\n";
    std::cout << "2. Adding 10 elements...\n";
    for (int i = 0; i < 10; ++i)
        container.push_back(i);

    printContainer(container, container.size(), "3. Contents: ");
    std::cout << "4. Size: " << container.size() << "\n";

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

    std::cout << "===================================================\n";
}

int main()
{
    std::cout << "========== CONTAINER DEMONSTRATION ==========\n";

    // Test sequential container
    SequentialContainer<int> seqContainer;
    testContainer(seqContainer, "SEQUENTIAL CONTAINER");

    // Test linked list container
    LinkedListContainer<int> listContainer;
    testContainer(listContainer, "LINKED LIST CONTAINER");

    return 0;
}