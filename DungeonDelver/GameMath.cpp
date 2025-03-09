#include "GameMath.h"

namespace DungeonDelver::System::Math
{
	bool IsBetween(int number, int min, int max, bool maxInclusive, bool minInclusive)
	{
		if (min > max)
		{
			int temp = min;
			min = max;
			max = temp;
		}

		if (min == max && !maxInclusive && !minInclusive)
		{
			throw std::invalid_argument("Error! Cannot find a number between the same number exclusively!");
		}

		if (!maxInclusive)
		{
			max--;
		}

		if (!minInclusive)
		{
			min++;
		}

		return number >= min && number <= max;
	}

	int Clamp(int value, int min, int max)
	{
		return value < min ? min : value > max ? max : value;
	}

	float Clamp(float value, float min, float max)
	{
		return value < min ? min : value > max ? max : value;
	}

	int RandomInt(int min, int max, bool maxInclusive, bool minInclusive)
	{
		static std::random_device rd;
		static std::mt19937 engine(rd());

		if (!maxInclusive)
			max--;

		if (!minInclusive)
			min++;

		std::uniform_int_distribution<int> dist(min, max);

		return dist(engine);
	}

	bool IsChanceSuccessful(int percentage)
	{
		if (percentage < 0 || percentage > 100)
		{
			throw std::invalid_argument("Percentage must be between 0-100 for testing chance!");
		}
		return RandomInt(1, 100) <= percentage;
	}

	float GetDistance(int x1, int y1, int x2, int y2)
	{
		int xDif = std::abs(x1 - x2);
		int yDif = std::abs(y1 - y2);

		float radicand = xDif * xDif + yDif * yDif;

		return std::sqrtf(radicand);
	}

	float RoundToPrecision(float value, int precision)
	{
		//Maximum float precision of 7
		if (precision > 7)
			precision = 7;
		float factor = std::pow(10.f, precision);
		return std::round(value * factor) / factor;
	}
}