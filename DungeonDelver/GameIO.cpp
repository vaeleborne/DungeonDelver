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

	bool IsAlphaNumeric(const std::string& string)
	{
		for (char c : string)
		{
			if (!std::isalnum(c))
				return false;
		}
		return true;
	}

	bool IsNumeric(const std::string& string)
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

	void ClearConsole(std::ostream& output)
	{

#ifdef _WIN32
		if (&output != &std::cout || system("cls") != 0)
		{
			output << "\x1b[2J\x1b[H";	//If clear fails, use ansi to 'clear' (scrolls down)
		}
#else
		if (&output != &std::cout || system("clear") != 0)
		{
			output << "\x1b[2J\x1b[H";	//If clear fails, use ansi to 'clear' (scrolls down)
		}
#endif // _WIN32

	}

	void WriteNewLines(std::ostream& output, int num)
	{
		for (int i = 0; i < num; i++)
			output << "\n";
	}

	void PressAnyKeyAlert(std::ostream& output, const std::string& message, bool clearConsole)
	{
		if (clearConsole)
		{
			ClearConsole(output);
		}

		if (message != "")
		{
			output << message << std::endl;
		}
		output << "Press Any Key To Continue...";
		GetKey();
		output << std::endl;
	}

	void PressAnyKeyAlert(std::ostream& output, bool clearConsole)
	{

		if (clearConsole)
		{
			ClearConsole(output);
		}
		output << "Press Any Key To Continue...";
		GetKey();
		output << std::endl;
	}

	void PressAnyKeyAlertInColor(std::ostream& output, const std::string& color, bool clearConsole)
	{

		if (clearConsole)
		{
			ClearConsole(output);
		}
		output << color << "Press Any Key To Continue..." << ANSI_RESET;
		GetKey();
		output << std::endl;
	}

	void PressAnyKeyAlertInColor(std::ostream& output, const std::string& message, const std::string& color, bool clearConsole)
	{

		if (clearConsole)
		{
			ClearConsole(output);
		}

		output << color;
		if (message != "")
		{
			output << message << "\n";
		}
		output << "Press Any Key To Continue..." << ANSI_RESET;
		GetKey();
		output << std::endl;
	}

	bool AskYesNo(std::ostream& output, const std::string& question, bool clearScreen)
	{
		bool validInput = false;
		do
		{
			if (clearScreen)
				ClearConsole(output);

			output << question << "\n" << "Input (y/n): ";

			char input = GetKey();


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
			FlushInputBuffer(std::cin);
			WriteNewLines(output);
			PressAnyKeyAlertInColor(output, "Invalid!", ANSI_RED, false);

		} while (!validInput);
	}

	bool AskYesNo(std::ostream& output, const std::string& question, const std::string& color, bool clearScreen)
	{
		bool validInput = false;
		do
		{
			if (clearScreen)
				ClearConsole(output);

			output << color << question << "\n" << "Input (y/n): " << ANSI_RESET;
			char input = GetKey();

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
			FlushInputBuffer(std::cin);
			WriteNewLines(output);
			PressAnyKeyAlertInColor(output, "Invalid!", ANSI_RED, false);

		} while (!validInput);
	}

	int GetIntFromUser(std::istream& in, std::ostream& output, int min, int max, bool clearConsole, bool inColor, const std::string& color)
	{
		int number = 0;
		bool valid = false;

		do
		{
			if (clearConsole)
				ClearConsole(output);
			if (inColor)
				output << color;


			output << "Please enter a number between " << min << " and " << max << " inclusively: ";
			std::string input = "";
			std::getline(in, input);
			FlushInputBuffer(in);

			if (IsNumeric(input))
			{
				number = std::stoi(input);

				if (DungeonDelver::System::Math::IsBetween(number, min, max))
				{
					valid = true;
				}
			}

			if (inColor)
				output << ANSI_RESET;

		} while (!valid);

		return number;
	}

	void WriteHeading(std::ostream& output, const std::string& heading, int minimumLength, int minimumPadding, bool clearConsole, bool inColor, const std::string& color)
	{
		if (clearConsole)
			ClearConsole(output);

		int headingWidth = static_cast<int>(heading.length());

		int width = std::max(headingWidth + (2 * minimumPadding), minimumLength);
		std::string line(width, '-');

		int padding = (width - headingWidth) / 2;             //Padding amount for the left       

		Write(output, line, true, inColor, color);
		Write(output, std::string(padding, ' ') + heading + std::string(padding, ' '), true, inColor, color);
		Write(output, line, true, inColor, color);
	}

	void FlushInputBuffer(std::istream& input)
	{
		input.clear();
		input.ignore(input.rdbuf()->in_avail());
	}

	int GetIndexOfUserChoice(std::ostream& output, const std::vector<std::string>& options, bool askInColor, const std::string& color)
	{
		if (options.empty())
			return -1;

		int index = 0;
		for (int i = 0; i < options.size(); i++)
		{
			Write(output, options[i], true, askInColor, color);
		}

		return index;
	}

	void Write(std::ostream& output, const std::string& message, bool newLine, bool inColor, const std::string& color)
	{
		if (inColor)
		{
			output << color << message << ANSI_RESET;
		}
		else
		{
			output << message;
		}

		if (newLine)
			output << "\n";
	}
}

	

