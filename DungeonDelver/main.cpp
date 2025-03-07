#include <iostream>
#include "GameIO.h"

#define io DungeonDelver::System::IO

int main()
{
    // Print "Hello World" in red
    io::WriteInColor("Hello World!", ANSI_RED, true);

	return 0;
}