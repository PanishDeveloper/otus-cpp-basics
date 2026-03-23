#include "demonstration.hpp"
#include <limits>

int main()
{
    SequentialContainer<int> seqContainer;
    DoublyLinkedList<int> doublyList;
    SinglyLinkedList<int> singlyList;

    int choice;
    do
    {
        showMenu();
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input! Please enter 1 - 5.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                testContainer(seqContainer, "SEQUENTIAL CONTAINER");
                break;
            case 2:
                testContainer(doublyList, "DOUBLY LINKED LIST");
                break;
            case 3:
                testContainer(singlyList, "SINGLY LINKED LIST");
                break;
            case 4:
                demonstrateMoveSemantics();
                demonstrateListMoveSemantics();
                break;
            case 5:
                std::cout << "\nExiting program. Goodbye!\n";
                break;
        default:
                std::cout << "\nInvalid input! Please enter 1 - 5.\n";
        }

    } while (choice != 5);

    return 0;
}
