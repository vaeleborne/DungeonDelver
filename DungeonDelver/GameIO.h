#ifndef GAME_IO_H
#define GAME_IO_H

#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif


#include "ANSI_Colors.h"

namespace DungeonDelver::System::IO
{

#ifdef _WIN32
	/// <summary>
	/// Gets a key press
	/// </summary>
	/// <returns>The character from the user</returns>
	int Getkey() { return _getch(); }
#else
	int Getkey() {
		termios oldt{}, newt{};
		int ch;

		// Get current terminal settings
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;

		// Disable canonical mode and echo
		newt.c_lflag &= ~(ICANON | ECHO);

		tcsetattr(STDIN_FILENO, TCSANOW, &newt);

		// Read single character
		ch = getchar();

		// Restore old settings
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

		return ch;
	}
#endif

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

	/// <summary>
	/// Cross platform way to clear the console, uses ANSI code, needs to be Windows 10+
	/// </summary>
	void ClearConsole()
	{
		std::cout << "\x1b[2J\x1b[H";
	}

	/// <summary>
	/// Flushes the cin buffer by clearing any cin flags and ignoring the buffer
	/// </summary>
	void FlushCinBuffer()
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}

	/// <summary>
	/// Function writes a number of new lines to the console, defaults to 1
	/// </summary>
	/// <param name="num">
	/// The number of new line characters to print
	/// </param>
	void WriteNewLines(int num = 1)
	{
		for (int i = 0; i < num; i++)
			std::cout << "\n";
	}

	/// <summary>
	/// Displays a message followed by a Press Any Key To Continue... message
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="message">The message to show the user</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlert(const std::string& message = "", bool clearConsole = false)
	{
		if (clearConsole)
		{
			ClearConsole();
		}

		if (message != "")
		{
			std::cout << message << std::endl;
		}
		std::cout << "Press Any Key To Continue...";
		Getkey();
		std::cout << std::endl;
	}

	/// <summary>
	/// Displays Press Any Key To Continue...
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlert(bool clearConsole)
	{

		if (clearConsole)
		{
			ClearConsole();
		}
		std::cout << "Press Any Key To Continue...";
		Getkey();
		std::cout << std::endl;
	}

	/// <summary>
	/// Displays Press Any Key To Continue... in a passed in color, or in RED by default
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="color">Color to write in</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlertInColor(const std::string& color, bool clearConsole)
	{

		if (clearConsole)
		{
			ClearConsole();
		}
		std::cout << color << "Press Any Key To Continue..." << ANSI_RESET;
		Getkey();
		std::cout << std::endl;
	}

	/// <summary>
	/// Displays a message followed by a Press Any Key To Continue... message
	/// These are displayed in a passed in color
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="message">Message to display</param>
	/// <param name="color">Color to write in</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlertInColor(const std::string& message, const std::string& color, bool clearConsole )
	{

		if (clearConsole)
		{
			ClearConsole();
		}

		std::cout << color;
		if (message != "")
		{
			std::cout << message  << "\n";
		}
		std::cout << "Press Any Key To Continue..." << ANSI_RESET;
		Getkey();
		std::cout << std::endl;
	}

	/// <summary>
	/// Ask a question to a user and gets either a 'y' or 'n', will loop asking until a 
	/// valid choice is chosen. If the user presses 'y' this will return true, if they
	/// press 'n' it will return false
	/// </summary>
	/// <param name="question">The question to ask</param>
	/// <param name="clearScreen">Bool to optionally clear the console</param>
	/// <returns></returns>
	bool AskYesNo(const std::string& question, bool clearScreen)
	{
		bool validInput = false;
		do
		{
			if (clearScreen)
				ClearConsole();

			std::cout << question << "\n" << "Input (y/n): ";

			char input = _getch();


			if (std::isalpha(input))
			{
				input = std::tolower(input);
				if (input == 'y')
				{
					return true;
				}
				else if (input == 'n')
				{
					return false;
				}
			}
			FlushCinBuffer();
			WriteNewLines();
			PressAnyKeyAlertInColor("Invalid!", ANSI_RED, false);

		} while (!validInput);

		//Handle asking a question
	}

	/// <summary>
	/// Ask a question to a user and gets either a 'y' or 'n', will loop asking until a 
	/// valid choice is chosen. If the user presses 'y' this will return true, if they
	/// press 'n' it will return false
	/// </summary>
	/// <param name="question">The question to ask</param>
	/// <param name="color">Color to ask question in</param>
	/// <param name="clearScreen">Bool to optionally clear the console</param>
	/// <returns></returns>
	bool AskYesNo(const std::string& question, const std::string& color, bool clearScreen)
	{
		bool validInput = false;
		do
		{
			if (clearScreen)
				ClearConsole();

			std::cout << color << question << "\n" << "Input (y/n): " << ANSI_RESET;
			char input = _getch();

			if (std::isalpha(input))
			{
				input = std::tolower(input);
				if (input == 'y')
				{
					return true;
				}
				else if (input == 'n')
				{
					return false;
				}
			}
			FlushCinBuffer();
			WriteNewLines();
			PressAnyKeyAlertInColor("Invalid!", ANSI_RED, false);

		} while (!validInput);
	}
}

#endif