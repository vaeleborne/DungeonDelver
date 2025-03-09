#include "GameMath.h"

namespace DungeonDelver::System::Math
{
	bool IsBetween(int number, int min, int max, bool inclusive)
	{
		if (min > max)
		{
			int temp = min;
			min = max;
			max = temp;
		}

		if (!inclusive)
		{
			if (min == max)
			{
				throw "Error! Cannot find a number between the same number exclusively!";
			}

			min++;
			max--;
		}

		return number >= min && number <= max;
	}
}