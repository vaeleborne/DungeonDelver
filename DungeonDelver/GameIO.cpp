#include "GameIO.h"
//Includes dependent on build system
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace DungeonDelver::System::IO
{

	int GetKey()
	{
#ifdef _WIN32
		return _getch();
#else
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
#endif
	}

	bool DungeonDelver::System::IO::IsAlphaNumeric(const std::string& string)
	{
		for (char c : string)
		{
			if (!std::isalnum(c))
				return false;
		}
		return true;
	}

	bool DungeonDelver::System::IO::IsNumeric(const std::string& string)
	{
		if (string.length() == 0)
			return false;

		std::string testStr = string;
		if (string.length() > 0 && string[0] == '-')
		{
			//Can still be numeric, just a negative
			testStr = string.substr(1);
		}

		for (char c : testStr)
		{
			if (!std::isdigit(c))
				return false;
		}
		return true;
	}

	void DungeonDelver::System::IO::WriteInColor(const std::string& message, const std::string& color, bool addNewLine)
	{
		std::cout << color << message << ANSI_RESET;

		if (addNewLine)
			std::cout << "\n";
	}

	void DungeonDelver::System::IO::ClearConsole()
	{
		//std::cout << "\x1b[2J\x1b[H";

#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif // _WIN32

	}

	void DungeonDelver::System::IO::FlushCinBuffer()
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}

	void DungeonDelver::System::IO::WriteNewLines(int num)
	{
		for (int i = 0; i < num; i++)
			std::cout << "\n";
	}

	void DungeonDelver::System::IO::PressAnyKeyAlert(const std::string& message, bool clearConsole)
	{
		if (clearConsole)
		{
			DungeonDelver::System::IO::ClearConsole();
		}

		if (message != "")
		{
			std::cout << message << std::endl;
		}
		std::cout << "Press Any Key To Continue...";
		DungeonDelver::System::IO::GetKey();
		std::cout << std::endl;
	}

	void DungeonDelver::System::IO::PressAnyKeyAlert(bool clearConsole)
	{

		if (clearConsole)
		{
			DungeonDelver::System::IO::ClearConsole();
		}
		std::cout << "Press Any Key To Continue...";
		DungeonDelver::System::IO::GetKey();
		std::cout << std::endl;
	}

	void DungeonDelver::System::IO::PressAnyKeyAlertInColor(const std::string& color, bool clearConsole)
	{

		if (clearConsole)
		{
			DungeonDelver::System::IO::ClearConsole();
		}
		std::cout << color << "Press Any Key To Continue..." << ANSI_RESET;
		DungeonDelver::System::IO::GetKey();
		std::cout << std::endl;
	}

	void DungeonDelver::System::IO::PressAnyKeyAlertInColor(const std::string& message, const std::string& color, bool clearConsole)
	{

		if (clearConsole)
		{
			DungeonDelver::System::IO::ClearConsole();
		}

		std::cout << color;
		if (message != "")
		{
			std::cout << message << "\n";
		}
		std::cout << "Press Any Key To Continue..." << ANSI_RESET;
		DungeonDelver::System::IO::GetKey();
		std::cout << std::endl;
	}

	bool DungeonDelver::System::IO::AskYesNo(const std::string& question, bool clearScreen)
	{
		bool validInput = false;
		do
		{
			if (clearScreen)
				DungeonDelver::System::IO::ClearConsole();

			std::cout << question << "\n" << "Input (y/n): ";

			char input = DungeonDelver::System::IO::GetKey();


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
			DungeonDelver::System::IO::FlushCinBuffer();
			DungeonDelver::System::IO::WriteNewLines();
			DungeonDelver::System::IO::PressAnyKeyAlertInColor("Invalid!", ANSI_RED, false);

		} while (!validInput);
	}

	bool DungeonDelver::System::IO::AskYesNo(const std::string& question, const std::string& color, bool clearScreen)
	{
		bool validInput = false;
		do
		{
			if (clearScreen)
				DungeonDelver::System::IO::ClearConsole();

			std::cout << color << question << "\n" << "Input (y/n): " << ANSI_RESET;
			char input = DungeonDelver::System::IO::GetKey();

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
			DungeonDelver::System::IO::FlushCinBuffer();
			DungeonDelver::System::IO::WriteNewLines();
			DungeonDelver::System::IO::PressAnyKeyAlertInColor("Invalid!", ANSI_RED, false);

		} while (!validInput);
	}

	int DungeonDelver::System::IO::GetIntFromUser(int min, int max, bool clearConsole, bool inColor, const std::string& color)
	{
		int number = 0;
		bool valid = false;

		do
		{
			if (clearConsole)
				DungeonDelver::System::IO::ClearConsole();
			if (inColor)
				std::cout << color;


			std::cout << "Please enter a number between " << min << " and " << max << " inclusively: ";
			std::string input = "";
			std::getline(std::cin, input);
			DungeonDelver::System::IO::FlushCinBuffer();

			if (DungeonDelver::System::IO::IsNumeric(input))
			{
				number = std::stoi(input);

				if (DungeonDelver::System::Math::IsBetween(number, min, max))
				{
					valid = true;
				}
			}

			if (inColor)
				std::cout << ANSI_RESET;

		} while (!valid);

		return number;
	}
}