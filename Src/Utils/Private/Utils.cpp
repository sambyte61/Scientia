#include "Utils.h"

#include <limits>

void ClearScreen()
{
    // ANSI escape code to clear the screen and move the cursor to top-left
    std::cout << "\033[2J\033[H";
}

void WaitForEnter()
{
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}