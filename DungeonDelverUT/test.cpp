#include "pch.h"
#include <sstream>
#include "../DungeonDelver/GameIO.h"


static TEST(OutputTests, WriteInColor_ExpectNoFatalError) {
	EXPECT_NO_FATAL_FAILURE({
		DungeonDelver::System::IO::Write(std::cout, "Hello Unit Tests!", true, true, ANSI_BLUE);
	});
}

static TEST(OutputTests, WriteHeading_ExpectNoFatalError) {
	EXPECT_NO_FATAL_FAILURE({
		DungeonDelver::System::IO::WriteHeading(std::cout, "TEST HEADING", 50, 5, false, true, ANSI_HI_MAGENTA);
		});
}

static TEST(OutputTests, WriteInColorMessage_ColorCodesAppear_NoNewLine)
{
	std::stringstream actual;
	std::stringstream expected;

	std::string color = ANSI_HI_YELLOW;
	std::string message = "TESTING MESSAGE";

	expected << color << message << ANSI_RESET;

	DungeonDelver::System::IO::Write(actual, message, false, true, color);

	EXPECT_EQ(expected.str(), actual.str());
}

static TEST(OutputTests, WriteInColorMessage_ColorCodesAppear_WithNewLine)
{
	std::stringstream actual;
	std::stringstream expected;

	std::string color = ANSI_HI_YELLOW;
	std::string message = "TESTING MESSAGE";

	expected << color << message << ANSI_RESET << "\n";

	DungeonDelver::System::IO::Write(actual, message, true, true, color);

	EXPECT_EQ(expected.str(), actual.str());
}

static TEST(InputTests, GetIntFromUser_ReturnsExpectedValues)
{
	std::istringstream mockInput("10\n");
	std::stringstream mockOutput;

	int expectedInt = 10;

	int actualInt = DungeonDelver::System::IO::GetIntFromUser(mockInput, mockOutput, -10, 10);

	EXPECT_EQ(expectedInt, actualInt);

	expectedInt = -10;
	mockInput.clear();
	mockInput.str("-10\n");
	actualInt = DungeonDelver::System::IO::GetIntFromUser(mockInput, mockOutput, -10, 10);
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

	int index = DungeonDelver::System::IO::GetIndexOfUserChoice(mockInput, mockOutput, options, true, ANSI_YELLOW);
	std::cout << "\n";

	EXPECT_EQ(0, index);

}
