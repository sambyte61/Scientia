#include <iostream>

#include "Matrix.h"

#include "Examples/Examples.h"

void option1() {
    cout << "You selected Option 1\n";
    // Do something for option 1
}

void option2() {
    cout << "You selected Option 2\n";
    // Do something for option 2
}

void printMenu() {
    std::cout << "\n===== MENU =====\n";
    std::cout << "1. Do Option 1\n";
    std::cout << "2. Do Option 2\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
}

enum class ExampleMenuOptions : uint8
{
    EXIT = 0,
    MATRIX = 1,
    VECTOR = 2
};

int main(int, char**)
{
    int OptionSelected;

    while (true) {
        printMenu();
        std::cin >> OptionSelected;

        if (cin.fail()) {
            cin.clear(); // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                option1();
                break;
            case 2:
                option2();
                break;
            case 0:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
