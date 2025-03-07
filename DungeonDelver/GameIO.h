#ifndef GAME_IO_H
#define GAME_IO_H
#include <iostream>
#include <string>
#include "ANSI_Colors.h"

namespace DungeonDelver::System::IO
{
	/// <summary>
	/// Writes a message to the console in a given color, default of white <br/> 
	/// Optionally, can print the new line character at the end of the message
	/// </summary>
	/// <param name="message">
	/// The message to display
	/// </param>
	/// <param name="color">
	/// The color (use ANSI_Colors.h)
	/// </param>
	/// <param name="addNewLine">
	/// If we want to print a new line
	/// </param>
	void WriteInColor(const std::string& message, const std::string& color = ANSI_WHITE, bool addNewLine = false)
	{
		std::cout << color << message << ANSI_RESET;

		if (addNewLine)
			std::cout << "\n";
	}
}

#endif