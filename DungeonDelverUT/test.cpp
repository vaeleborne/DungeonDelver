#include "pch.h"
#include "../DungeonDelver/GameIO.h"


static TEST(OUTPUT, WRITEINCOLOR_NO_FATAL_ERROR) {
	EXPECT_NO_FATAL_FAILURE({
		DungeonDelver::System::IO::WriteInColor("Hello Unit Tests!", ANSI_BLUE, true);
	});
}

static TEST(OUTPUT, WRITEHEADING_NO_FATAL_ERROR) {
	EXPECT_NO_FATAL_FAILURE({
		DungeonDelver::System::IO::WriteHeading(std::cout, "TEST HEADING", false, true, ANSI_HI_MAGENTA);
		});
}