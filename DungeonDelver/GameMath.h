#ifndef GAME_MATH_H
#define GAME_MATH_H
#include <stdexcept>
#include <random>
#include <math.h>
#include <cmath>
#include <string>
#include <sstream>

namespace DungeonDelver::System::Math
{
	/// <summary>
	/// Checks to see if a number is between two numbers
	/// Can choose inclusivity of min and max
	/// </summary>
	/// <param name="number">Number to Check</param>
	/// <param name="min">Minimum number</param>
	/// <param name="max">Maximum number</param>
	/// <param name="maxInclusive">Whether the max is inclusive</param>
	/// <param name="minInclusive">Whether the min is inclusive</param>
	/// <returns></returns>
	bool IsBetween(int number, int min, int max, bool maxInclusive = true, bool minInclusive = true);

	/// <summary>
	/// Clamps an integer
	/// </summary>
	/// <param name="value">The value to clamp</param>
	/// <param name="min">The minimum value the input should be</param>
	/// <param name="max">The maximum value the input should be</param>
	/// <returns>A clamped value</returns>
	int Clamp(int value, int min, int max);

	/// <summary>
	/// Clamps a float
	/// </summary>
	/// <param name="value">The value to clamp</param>
	/// <param name="min">The minimum value the input should be</param>
	/// <param name="max">The maximum value the input should be</param>
	/// <returns>A clamped value</returns>
	float Clamp(float value, float min, float max);

	/// <summary>
	/// Returns a random int within a given range, can choose to make min
	/// or max excelusive or inclusive
	/// </summary>
	/// <param name="min">Minimum value</param>
	/// <param name="max">Maximum value</param>
	/// <returns>A random number between min and max</returns>
	int RandomInt(int min, int max, bool maxInclusive = true, bool minInclusive = true);

	/// <summary>
	/// Returns true or false given a probability (0-100%),
	/// throws an error if percentage is out of range
	/// </summary>
	/// <param name="percentage">The probability to return true (0-100)</param>
	/// <returns>
	/// True if a roll was successful
	/// </returns>
	bool IsChanceSuccessful(int percentage);

	/// <summary>
	/// Rounds a float to a given precision value
	/// </summary>
	/// <param name="value">Value to round</param>
	/// <param name="precision">Precision to go to</param>
	/// <returns>A float rounded to a given precision</returns>
	float RoundToPrecision(float value, int precision);

	/// <summary>
	/// Gets the distance between two points
	/// </summary>
	/// <returns>The distance between 2 points, linearly</returns>
	float GetDistance(int x1, int y1, int x2, int y2);

}
#endif