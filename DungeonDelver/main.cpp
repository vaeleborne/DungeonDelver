#include <iostream>
#include "GameIO.h"

#define io DungeonDelver::System::IO

int main()
{
    // Print "Hello World" in red
    io::WriteInColor("Hello World!", ANSI_RED, true);

    if (io::AskYesNo("Please enter y", ANSI_YELLOW, false))
    {
        std::cout << "\nThank you!";
    }
    else
    {
        std::cout << "\nHey!";
    }

	return 0;
}