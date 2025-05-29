#include <iostream>

#include "Utils.h"
#include "Matrices.h"

void PrintMenu()
{
    std::cout << "\n===== EXAMPLES MENU =====\n";
    std::cout << "1. Matrices\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
}

enum class ExampleMenuOptions : uint8_t
{
    EXIT = 0,
    MATRIX = 1,
    VECTOR = 2
};

int RunExamples()
{
    int OptionSelected;

    ClearScreen();

    while (true)
    {
        PrintMenu();

        std::cin >> OptionSelected;
        ExampleMenuOptions MenuOptionSelected = static_cast<ExampleMenuOptions>(OptionSelected);

        if (std::cin.fail())
        {
            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (MenuOptionSelected)
        {
            case ExampleMenuOptions::MATRIX:
            {
                RunMatrixExample();
                WaitForEnter();

                break;
            }
            case ExampleMenuOptions::EXIT:
            {
                return 0;
            }
            default:
            {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }

        ClearScreen();
    }

    return 0;
}
