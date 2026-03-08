#include "demonstration.hpp"


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
            std::cout << "\nInvalid input! Please enter 1 - 4.\n";
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
                std::cout << "\nExiting program. Goodbye!\n";
                break;
        default:
                std::cout << "\nInvalid input! Please enter 1 - 4.\n";
        }

    } while (choice != 4);

    return 0;
}
