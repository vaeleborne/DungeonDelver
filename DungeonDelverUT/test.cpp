#include "pch.h"
#include <sstream>
#include "../DungeonDelver/GameIO.h"


static TEST(OutputTests, WriteInColor_ExpectNoFatalError) {
	EXPECT_NO_FATAL_FAILURE({
		DungeonDelver::System::IO::WriteInColor(std::cout, "Hello Unit Tests!", ANSI_BLUE, true);
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

	DungeonDelver::System::IO::WriteInColor(actual, message, color);

	EXPECT_EQ(expected.str(), actual.str());
}

static TEST(OutputTests, WriteInColorMessage_ColorCodesAppear_WithNewLine)
{
	std::stringstream actual;
	std::stringstream expected;

	std::string color = ANSI_HI_YELLOW;
	std::string message = "TESTING MESSAGE";

	expected << color << message << ANSI_RESET << "\n";

	DungeonDelver::System::IO::WriteInColor(actual, message, color, true);

	EXPECT_EQ(expected.str(), actual.str());
}