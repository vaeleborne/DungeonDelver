#ifndef GAME_IO_H
#define GAME_IO_H

#include <iostream>
#include <string>
#include <vector>
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
	void WriteNewLines(std::ostream& output = std::cout, unsigned int num = 1);

	/// <summary>
	/// Displays a message followed by a Press Any Key To Continue... message
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="message">The message to show the user</param>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlert(std::ostream& output, const std::string& message = "", bool clearConsole = false, bool inColor = false, const std::string& color = ANSI_WHITE);

	/// <summary>
	/// Displays Press Any Key To Continue...
	/// Then waits for the user to press a key before returning
	/// </summary>
	/// <param name="clearConsole">Bool to optionally clear the console</param>
	void PressAnyKeyAlert(std::ostream& output, bool clearConsole, bool inColor = false, const std::string& color = ANSI_WHITE);

	/// <summary>
	/// Ask a question to a user and gets either a 'y' or 'n', will loop asking until a 
	/// valid choice is chosen. If the user presses 'y' this will return true, if they
	/// press 'n' it will return false
	/// </summary>
	/// <param name="question">The question to ask</param>
	/// <param name="clearScreen">Bool to optionally clear the console</param>
	/// <returns></returns>
	bool AskYesNo(std::ostream& output, const std::string& question, bool clearScreen, bool inColor = false, const std::string& color = ANSI_WHITE);

	/// <summary>
	/// Get an integer between two numbers from a user inclusively, can pass "" as custom message to get a default <br/>
	/// Message asking the user to enter a number between the two values inclusively
	/// </summary>
	/// <param name="in">The input stream to use</param>
	/// <param name="min">Minimum value</param>
	/// <param name="customMessage">Optional to display a custom prompt, enter "" for default</param>
	/// <param name="max">Maximum value</param>
	/// <param name="clearConsole">Whether or not to clear the console when asking</param>
	/// <param name="inColor">Whether or not to ask in a color</param>
	/// <param name="color">The color to ask in if applicable</param>
	/// <returns>An integer between min and max either inclusively</returns>
	int GetIntFromUser(std::istream& in, std::ostream& output, int min, int max,  std::string customMessage = "", bool clearConsole = false, bool inColor = false, const std::string & color = ANSI_WHITE);

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

	/// <summary>
	/// Takes a vector of strings that are 'options' to display to the user. <br/>
	/// Displays them with a number that starts at 1 such as 1) Option 1 <br/>
	/// Gets a valid corresponding number from the user, will loop asking for a number if invalid but not clear console. <br/>
	/// Returns the index equivalent of the users choice, ie if they enter 1 for option 1 this will return 0 so you can index the vector.<br/>
	/// If an empty vector is passed in this will return -1!
	/// </summary>
	/// <param name="input">The input stream to use</param>
	/// <param name="output">The output stream to use</param>
	/// <param name="options">A vector containing options</param>
	/// <param name="askInColor">Option to ask in color</param>
	/// <param name="color">The color to write in if askInColor is true</param>
	/// <returns>
	/// The index of the option a user chooses, or -1 
	/// </returns>
	int GetIndexOfUserChoice(std::istream& input, std::ostream& output, const std::vector<std::string>& options, bool askInColor = false, const std::string& color = ANSI_WHITE);

	/// <summary>
	/// Writes a message to an output stream, optionally writes it in a color with a default of white <br/> 
	/// If inColor is true but no color is given. Uses an ANSI escape sequence to color the text, this won't work<br/> 
	/// On older windows systems or out streams that can't handle them. 
	/// Optionally, can print the new line character at the end of the message
	/// </summary>
	/// <param name="output">The output stream</param>
	/// <param name="message">The message to write</param>
	/// <param name="newLine">Determines if we add a newline at the end</param>
	/// <param name="inColor">Determines if we write in a specific color</param>
	/// <param name="color">The color to write the text in</param>
	void Write(std::ostream& output, const std::string& message, bool newLine = false, bool inColor = false, const std::string& color = ANSI_WHITE);


}

#endif