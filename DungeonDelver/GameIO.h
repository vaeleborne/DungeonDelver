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

	bool IsAlphaNumeric(const std::string& string);

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
	void WriteInColor(const std::string& message, const std::string& color = ANSI_WHITE, bool addNewLine = false);

	/// <summary>
	/// Cross platform way to clear the console
	/// </summary>
	void ClearConsole();

	/// <summary>
	/// Flushes the cin buffer by clearing any cin flags and ignoring the buffer
	/// </summary>
	void FlushCinBuffer();

	/// <summary>
	/// Function writes a number of new lines to the console, defaults to 1
	/// </summary>
	/// <param name="num">
	/// The number of new line characters to print
	/// </param>
	void WriteNewLines(int num = 1);

	/// <summary>
	/// Displays a message followed by a Press Any Key To Continue... message
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="message">The message to show the user</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlert(const std::string& message = "", bool clearConsole = false);

	/// <summary>
	/// Displays Press Any Key To Continue...
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlert(bool clearConsole);

	/// <summary>
	/// Displays Press Any Key To Continue... in a passed in color, or in RED by default
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="color">Color to write in</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlertInColor(const std::string& color, bool clearConsole);

	/// <summary>
	/// Displays a message followed by a Press Any Key To Continue... message
	/// These are displayed in a passed in color
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="message">Message to display</param>
	/// <param name="color">Color to write in</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlertInColor(const std::string& message, const std::string& color, bool clearConsole);

	/// <summary>
	/// Ask a question to a user and gets either a 'y' or 'n', will loop asking until a 
	/// valid choice is chosen. If the user presses 'y' this will return true, if they
	/// press 'n' it will return false
	/// </summary>
	/// <param name="question">The question to ask</param>
	/// <param name="clearScreen">Bool to optionally clear the console</param>
	/// <returns></returns>
	bool AskYesNo(const std::string& question, bool clearScreen);

	/// <summary>
	/// Ask a question to a user and gets either a 'y' or 'n', will loop asking until a 
	/// valid choice is chosen. If the user presses 'y' this will return true, if they
	/// press 'n' it will return false
	/// </summary>
	/// <param name="question">The question to ask</param>
	/// <param name="color">Color to ask question in</param>
	/// <param name="clearScreen">Bool to optionally clear the console</param>
	/// <returns></returns>
	bool AskYesNo(const std::string& question, const std::string& color, bool clearScreen);

	int GetIntFromUser(int min, int max, bool clearConsole = false, bool inColor = false, const std::string& color = ANSI_WHITE);
}

#endif