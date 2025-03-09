/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: This file contains comprhensive unit testing for
* the DungeonDelver library's Math functions within the
* DungeonDelver::System::Math namespace.
*******************************************************************/

#include "pch.h"
#include <sstream>
#include "../DungeonDelver/GameMath.hpp"

namespace mth = DungeonDelver::System::Math;

static TEST(MathTests, IsBetween_ReturnsExpectedResults)
{
	EXPECT_TRUE(mth::IsBetween(1, 0, 10));
	EXPECT_TRUE(mth::IsBetween(0, 0, 10));
	EXPECT_TRUE(mth::IsBetween(10, 0, 10));
	EXPECT_TRUE(mth::IsBetween(1, -10, 10));
	EXPECT_TRUE(mth::IsBetween(-5, -10, 10));
	EXPECT_TRUE(mth::IsBetween(-5, -10, -2));

	//Test passing a number higher as min and lower as max, function should autocorrect it!
	EXPECT_TRUE(mth::IsBetween(5, 10, 1));
	EXPECT_TRUE(mth::IsBetween(5, 10, -1));

	//Test Exclusive Cases
	EXPECT_FALSE(mth::IsBetween(10, 1, 10, false));
	EXPECT_FALSE(mth::IsBetween(1, 1, 10, true, false));
}

static TEST(MathTests, IsBetween_ThrowsErrorWhenExclusiveAndMinEqualsMax)
{
	EXPECT_THROW(mth::IsBetween(1, 1, 1, false, false), std::invalid_argument);
}

static TEST(MathTests, IntClamp_ClampsProperly)
{
	int value = 6;
	EXPECT_EQ(5, mth::Clamp(value, 1, 5));
	EXPECT_EQ(7, mth::Clamp(value, 7, 10));
	EXPECT_EQ(5, mth::Clamp(value, 5, 5));

	EXPECT_EQ(20, mth::Clamp(value, 20, 30));

	EXPECT_EQ(-2, mth::Clamp(value, -10, -2));

	EXPECT_EQ(6, mth::Clamp(value, 6, 7));
}

static TEST(MathTests, FloatClamp_ClampsProperly)
{
	float value = 3.14;

	EXPECT_EQ(3.14f, mth::Clamp(value,3.14f, 10.f));
	EXPECT_EQ(3.14f, mth::Clamp(value, 0.f, 3.14f));

	EXPECT_EQ(3.72f, mth::Clamp(value, 3.72f, 10.f));

	EXPECT_EQ(2.12f, mth::Clamp(value, 1.1f, 2.12f));

	EXPECT_EQ(-5.3f, mth::Clamp(value, -10.f, -5.3f));
}

static TEST(MathTests, RandomInt_LikelyGettingRandomValuesWithinRange)
{
	/*
		Probability of getting a number in our testing range of 1-100 (or an equivalent range)

		P = 1/100

		Probability of getting the same number n times in a row is P^n

		An n of 10 gives a 1e-20 percent odds. We will use this as a base line
		If we get a number 10 times in a row, there may be something wrong, run the test once more but then check implementation

		To Test For Inclusivity, we will one, always check if the number is out of range
		But we will want to test getting the min value and the max value

		P = 1 - (99/100)^n 

		An n of 2000 gives roughly a 99.9999998 chance of occuring. So, while more expensive, we will loop 2000 times checking for min and max. If this fails, run test once more then 
		check implementation
	*/

	int numInRow = 0;
	int prevNum = 0;
	int num = mth::RandomInt(1, 100);
	bool foundMin = false;
	bool foundMax = false;
	bool seemsRandom = false;

	if (num == 1)
		foundMin = true;

	if (num == 100)
		foundMax = true;

	if (num >= 1 && num <= 100)
	{
		seemsRandom = true;
		prevNum = num;
		numInRow = 1;

		for (int i = 0; i < 2000; i++)
		{
			num = mth::RandomInt(1, 100);
			if (num < 1 || num > 100)
			{
				seemsRandom = false;
				break;
			}

			if (num == prevNum)
				numInRow++;
			else
				numInRow = 1;

			if (numInRow >= 10)
			{
				seemsRandom = false;
				break;
			}

			if (num == 1)
				foundMin = true;

			if (num == 100)
				foundMax = true;
			
		}
		if (seemsRandom)
		{
			seemsRandom = foundMin && foundMax;
		}
		
	}
	else
	{
		seemsRandom = false;
	}

	EXPECT_TRUE(seemsRandom);

	EXPECT_TRUE(mth::RandomInt(-10, -5) < 0);
}

static TEST(MathTests, IsChanceSuccessful_ThrowsErrorWhenOutOfRangeParameter)
{
	EXPECT_THROW(mth::IsChanceSuccessful(-1), std::invalid_argument);
	EXPECT_THROW(mth::IsChanceSuccessful(101), std::invalid_argument);
}

static TEST(MathTests, IsChanceSuccessful_ReturnsTrueWhen100Percent)
{
	EXPECT_TRUE(mth::IsChanceSuccessful(100));
}

static TEST(MathTests, IsChanceSuccessful_ReturnsFalseWhen0Percent)
{
	EXPECT_FALSE(mth::IsChanceSuccessful(0));
}

static TEST(MathTests, IsChanceSuccessful_LikelyWorksTestingFiftyFifty)
{

	/*
		With a 50/50 there is a 0.5 chance that one call will be successful and the same for it to not be

		Odds of one thing occuring with a 50% chance after n times is 1-0.5^n 

		We will use an n of 30 makes us EXTREMELY likely to have a specific result at least once (99.999999907%)
	*/

	bool gotAFalse = false;
	bool gotATrue = false;
	bool likelyWorking = false;

	for (int i = 0; i < 30; i++)
	{
		if (mth::IsChanceSuccessful(50))
			gotATrue = true;
		else
			gotAFalse = true;

		if (gotATrue && gotAFalse)
		{
			likelyWorking = true;
			break;
		}
	}

	EXPECT_TRUE(likelyWorking);
}

static TEST(MathTests, GetDistance_ReturnsExpectedValues)
{
	int x1 = 2;
	int x2 = 4;
	int y1 = 4;
	int y2 = 2;
	
	float expected = 2.828427f;	//Sqrt of 8

	EXPECT_NEAR(expected, mth::GetDistance(x1, y1, x2, y2), 1e-5);
}

static TEST(MathTests, RoundToPrecision_RoundsFloatsCorrectly)
{
	float pi = 3.141592;

	float shortPi = 3.14f;
	float moderatePi = 3.142f;
	float zeroPi = 3.f;
	float longPi = 3.141592f;

	EXPECT_EQ(shortPi, mth::RoundToPrecision(pi, 2));
	EXPECT_EQ(moderatePi, mth::RoundToPrecision(pi, 3));
	EXPECT_EQ(zeroPi, mth::RoundToPrecision(pi, 0));
	EXPECT_EQ(longPi, mth::RoundToPrecision(pi, 200));
}

