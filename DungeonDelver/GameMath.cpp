#include "GameMath.h"

namespace DungeonDelver::System::Math
{
	bool IsBetween(int number, int min, int max, bool inclusive)
	{
		if (!inclusive)
		{
			min++;
			max--;
		}

		return number >= min && number <= max;
	}
}