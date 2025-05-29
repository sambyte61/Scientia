#include <iostream>

#include "Utils.h"
#include "Examples/Examples.h"

void PrintMainMenu()
{
    std::cout << "\n===== MAIN MENU =====\n";
    std::cout << "1. Run examples\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
}

enum class MainMenuOptions : uint8_t
{
    EXIT = 0,
    EXAMPLES = 1
};

int main(int, char**)
{
    int OptionSelected;

    while (true)
    {
        ClearScreen();
        PrintMainMenu();

        std::cin >> OptionSelected;
        MainMenuOptions MenuOptionSelected = static_cast<MainMenuOptions>(OptionSelected);

        if (std::cin.fail())
        {
            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (MenuOptionSelected)
        {
            case MainMenuOptions::EXAMPLES:
            {
                RunExamples();
                break;
            }
            case MainMenuOptions::EXIT:
            {
                return 0;
            }
            default:
            {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    return 0;
}
