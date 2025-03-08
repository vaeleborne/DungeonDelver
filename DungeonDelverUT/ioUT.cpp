/*******************************************************************
* AUTHOR: Dylan Morgan
* 
* DESCRIPTION: This file contains comprhensive unit testing for
* the DungeonDelver library's GameIO functions within the 
* DungeonDelver::System::IO namespace. 
*******************************************************************/

#include "pch.h"
#include <sstream>
#include "../DungeonDelver/GameIO.h"


namespace io = DungeonDelver::System::IO;

//LOGIC TESTING

static TEST(LogicTests, IsAlphaNumeric_ReturnsExpectedValues)
{
	EXPECT_TRUE(io::IsAlphaNumeric("A"));
	EXPECT_TRUE(io::IsAlphaNumeric("b"));
	EXPECT_TRUE(io::IsAlphaNumeric("9"));
	EXPECT_TRUE(io::IsAlphaNumeric("9223372036854775807000")); //BIG NUMBER STILL NUMERIC EVEN IF GREATER THAN INT
	EXPECT_TRUE(io::IsAlphaNumeric("adfjsdkjkselkrFWASR11434353634"));	//LETTERS AND NUMBERS

	EXPECT_FALSE(io::IsAlphaNumeric(""));
	EXPECT_FALSE(io::IsAlphaNumeric("-"));
	EXPECT_FALSE(io::IsAlphaNumeric("-1"));			//NEGATIVE NUMBERS ARE NOT CONSIDERED ALPHA-NUMERIC, THEY ARE HOWEVER NUMERIC
	EXPECT_FALSE(io::IsAlphaNumeric("-23298"));
	EXPECT_FALSE(io::IsAlphaNumeric("!@"));
	EXPECT_FALSE(io::IsAlphaNumeric("123+"));
	EXPECT_FALSE(io::IsAlphaNumeric("Abc123*"));
}

static TEST(LogicTests, IsNumeric_ReturnsExpectedValues)
{
	EXPECT_TRUE(io::IsNumeric("1"));
	EXPECT_TRUE(io::IsNumeric("-1"));
	EXPECT_TRUE(io::IsNumeric("9223372036854775807000")); //BIG NUMBER STILL NUMERIC EVEN IF GREATER THAN INT
	EXPECT_TRUE(io::IsNumeric("-9223372036854775807000"));

	EXPECT_FALSE(io::IsNumeric(""));
	EXPECT_FALSE(io::IsNumeric("-"));
	EXPECT_FALSE(io::IsNumeric("24a"));
	EXPECT_FALSE(io::IsNumeric("24a5"));
	EXPECT_FALSE(io::IsNumeric("a"));
	EXPECT_FALSE(io::IsNumeric("hello"));
}


//OUTPUT TESTING

static TEST(OutputTests, Write_InColor_ExpectNoFatalError) {
	EXPECT_NO_FATAL_FAILURE({
		io::Write(std::cout, "Hello Unit Tests!", true, true, ANSI_BLUE);
	});
}

static TEST(OutputTests, WriteHeading_InColor_ExpectNoFatalError) {
	EXPECT_NO_FATAL_FAILURE({
		io::WriteHeading(std::cout, "TEST HEADING", 50, 5, false, true, ANSI_HI_MAGENTA);
		});
}

static TEST(OutputTests, Write_CorrectMessageGoesToOutput)
{
	std::stringstream actualOutput;
	std::stringstream expectedOutput;

	std::string message = "TESTING MESSAGE";

	expectedOutput << message;

	io::Write(actualOutput, message, false);

	EXPECT_EQ(expectedOutput.str(), actualOutput.str());
}

static TEST(OutputTests, Write_InColor_CorrectMessageGoesToOutput_WithColorEscapeCodes_NoNewLine)
{
	std::stringstream actualOutput;
	std::stringstream expectedOutput;

	std::string color = ANSI_HI_YELLOW;
	std::string message = "TESTING MESSAGE";

	expectedOutput << color << message << ANSI_RESET;

	io::Write(actualOutput, message, false, true, color);

	EXPECT_EQ(expectedOutput.str(), actualOutput.str());
}

static TEST(OutputTests, Write_InColor_CorrectMessageGoesToOutput_WithColorEscapeCodes_WithNewLine)
{
	std::stringstream actual;
	std::stringstream expected;

	std::string color = ANSI_HI_YELLOW;
	std::string message = "TESTING MESSAGE";

	expected << color << message << ANSI_RESET << "\n";

	io::Write(actual, message, true, true, color);

	EXPECT_EQ(expected.str(), actual.str());
}

static TEST(OutputTests, ClearConsole_SendsClearEscapeSequenceForNonNativeConsoleOutput)
{
	std::stringstream actualOutput;
	io::ClearConsole(actualOutput);

	EXPECT_EQ("\x1b[2J\x1b[H", actualOutput.str());
}

static TEST(OutputTests, WriteNewLines_AddsOneNewLineByDefault)
{
	std::stringstream actual;
	std::stringstream expected;

	expected << "\n";

	io::WriteNewLines(actual);
	EXPECT_EQ(expected.str(), actual.str());
}

static TEST(OutputTests, WriteNewLines_AddsCorrectNumberOfLinesWhenNumberPassedIn)
{
	std::stringstream actual;
	std::stringstream expected;

	expected << "\n\n\n\n";

	io::WriteNewLines(actual, 4);
	EXPECT_EQ(expected.str(), actual.str());
	expected << "\n\n";
	io::WriteNewLines(actual, 2);
	EXPECT_EQ(expected.str(), actual.str());

}

static TEST(OutputTests, WriteNewLines_ThrowsErrorIfZeroIsPassedIn)
{
	EXPECT_THROW(io::WriteNewLines(std::cout, 0), std::invalid_argument);
}

static TEST(OutputTests, PressAnyKeyAlert_NoAdditionalMessage_ShowsCorrectPrompt_NoColor_NoClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;

	expected << "Press Any Key To Continue...\n";
	io::PressAnyKeyAlert(std::cin, actual, false);
	EXPECT_EQ(expected.str(), actual.str());
}

static TEST(OutputTests, PressAnyKeyAlert_NoAdditionalMessage_ShowsCorrectPrompt_NoColor_WithClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;


	expected << "\x1b[2J\x1b[HPress Any Key To Continue...\n";
	io::PressAnyKeyAlert(std::cin, actual, true);
	EXPECT_EQ(expected.str(), actual.str());
}

static TEST(OutputTests, PressAnyKeyAlert_NoAdditionalMessage_ShowsCorrectPrompt_WithColor_WithClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;

	expected << "\x1b[2J\x1b[H" << ANSI_BLUE <<  "Press Any Key To Continue...\n" << ANSI_RESET;
	io::PressAnyKeyAlert(std::cin, actual, true, true, ANSI_BLUE);
	EXPECT_EQ(expected.str(), actual.str());
}

static TEST(OutputTests, PressAnyKeyAlert_NoAdditionalMessage_ShowsCorrectPrompt_WithColor_NoClearConsole)
{

}


//TODO: Add Inputstream method to the press any key alert,

static TEST(OutputTests, PressAnyKeyAlert_CustomAdditionalMessage_ShowsCorrectPrompt_NoColor_NoClearConsole)
{

}

static TEST(OutputTests, PressAnyKeyAlert_CustomAdditionalMessage_ShowsCorrectPrompt_NoColor_WithClearConsole)
{

}

static TEST(OutputTests, PressAnyKeyAlert_CustomAdditionalMessage_ShowsCorrectPrompt_WithColor_WithClearConsole)
{

}

static TEST(OutputTests, PressAnyKeyAlert_CustomAdditionalMessage_ShowsCorrectPrompt_WithColor_NoClearConsole)
{

}

//INPUT TESTING


static TEST(InputTests, GetIntFromUser_ReturnsExpectedValues)
{
	std::istringstream mockInput("10\n");
	std::stringstream mockOutput;

	int expectedInt = 10;

	int actualInt = io::GetIntFromUser(mockInput, mockOutput, -10, 10);

	EXPECT_EQ(expectedInt, actualInt);

	expectedInt = -10;
	mockInput.clear();
	mockInput.str("-10\n");
	actualInt = io::GetIntFromUser(mockInput, mockOutput, -10, 10);
	EXPECT_EQ(expectedInt, actualInt);
}

static TEST(InputTests, GetIndexOfUserChoice_ReturnsProperIndex)
{
	std::vector<std::string> options;

	options.push_back("Option 1");
	options.push_back("Option 2");
	options.push_back("Option 3");

	std::istringstream mockInput("1\n");
	std::stringstream mockOutput;

	int index = io::GetIndexOfUserChoice(mockInput, mockOutput, options, true, ANSI_YELLOW);
	std::cout << "\n";

	EXPECT_EQ(0, index);

}
