#ifndef GAME_IO_H
#define GAME_IO_H

#include <iostream>
#include <string>
#include "ANSI_Colors.h"
#include "GameMath.h"

namespace DungeonDelver::System::IO
{	
	/// <summary>
	/// Gets a key press
	/// </summary>
	/// <returns>The character from the user</returns>
	int GetKey();

	/// <summary>
	/// Function to check if a string is alpha numeric
	/// </summary>
	/// <param name="string">The string to test</param>
	/// <returns>True if the string is alpha numeric, false otherwise</returns>
	bool IsAlphaNumeric(const std::string& string);

	/// <summary>
	/// Checks if a string is numeric
	/// </summary>
	/// <param name="string">String to test</param>
	/// <returns>True if the string is numeric (including a negative), false otherwise</returns>
	bool IsNumeric(const std::string& string);

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
	void WriteInColor(std::ostream& output, const std::string& message, const std::string& color = ANSI_WHITE, bool addNewLine = false);

	/// <summary>
	/// Cross platform way to clear the console
	/// </summary>
	void ClearConsole(std::ostream& output = std::cout);

	/// <summary>
	/// Flushes the input buffer by clearing any cin flags and ignoring the buffer
	/// </summary>
	void FlushInputBuffer(std::istream& input = std::cin);

	/// <summary>
	/// Function writes a number of new lines to the console, defaults to 1
	/// </summary>
	/// <param name="num">
	/// The number of new line characters to print
	/// </param>
	void WriteNewLines(std::ostream& output = std::cout, int num = 1);

	/// <summary>
	/// Displays a message followed by a Press Any Key To Continue... message
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="message">The message to show the user</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlert(std::ostream& output, const std::string& message = "", bool clearConsole = false);

	/// <summary>
	/// Displays Press Any Key To Continue...
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlert(std::ostream& output, bool clearConsole);

	/// <summary>
	/// Displays Press Any Key To Continue... in a passed in color, or in RED by default
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="color">Color to write in</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlertInColor(std::ostream& output, const std::string& color, bool clearConsole);

	/// <summary>
	/// Displays a message followed by a Press Any Key To Continue... message
	/// These are displayed in a passed in color
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="message">Message to display</param>
	/// <param name="color">Color to write in</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlertInColor(std::ostream& output, const std::string& message, const std::string& color, bool clearConsole);

	/// <summary>
	/// Ask a question to a user and gets either a 'y' or 'n', will loop asking until a 
	/// valid choice is chosen. If the user presses 'y' this will return true, if they
	/// press 'n' it will return false
	/// </summary>
	/// <param name="question">The question to ask</param>
	/// <param name="clearScreen">Bool to optionally clear the console</param>
	/// <returns></returns>
	bool AskYesNo(std::ostream& output, const std::string& question, bool clearScreen);

	/// <summary>
	/// Ask a question to a user and gets either a 'y' or 'n', will loop asking until a 
	/// valid choice is chosen. If the user presses 'y' this will return true, if they
	/// press 'n' it will return false
	/// </summary>
	/// <param name="question">The question to ask</param>
	/// <param name="color">Color to ask question in</param>
	/// <param name="clearScreen">Bool to optionally clear the console</param>
	/// <returns></returns>
	bool AskYesNo(std::ostream& output, const std::string& question, const std::string& color, bool clearScreen);

	/// <summary>
	/// Get an integer between two numbers from a user inclusively
	/// </summary>
	/// <param name="in">The input stream to use</param>
	/// <param name="min">Minimum value</param>
	/// <param name="max">Maximum value</param>
	/// <param name="clearConsole">Whether or not to clear the console when asking</param>
	/// <param name="inColor">Whether or not to ask in a color</param>
	/// <param name="color">The color to ask in if applicable</param>
	/// <returns>An integer between min and max either inclusively</returns>
	int GetIntFromUser(std::istream& in, std::ostream& output, int min, int max, bool clearConsole = false, bool inColor = false, const std::string& color = ANSI_WHITE);

	/// <summary>
	/// Writes a centered heading based on a minimum length and a minimum padding value
	/// EXAMPLE: to center 'word' if minimum length is 40 padding on each side would be 
	/// the 40 - the length of 'word' divided by two. But if minimum length is say 2 and minimum padding is 5
	/// the padding on each side will be 5
	/// </summary>
	/// <param name="mimimumLength">The minimum length of the heading</param>
	/// <param name="minimumPadding">The minimum amount of padding we will have</param>
	/// <param name="output">The output stream</param>
	/// <param name="heading">The heading to write</param>
	/// <param name="clearConsole">If we want to clear the console/stream</param>
	/// <param name="inColor">If we want to write in color</param>
	/// <param name="color">The color to write in if applicable</param>
	void WriteHeading(std::ostream& output, const std::string& heading, int minimumLength = 60, int minimumPadding = 5, 
		bool clearConsole = false, bool inColor = false, const std::string& color = ANSI_WHITE);
}

#endif