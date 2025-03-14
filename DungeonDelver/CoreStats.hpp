#ifndef CORESTATS_HPP
#define CORESTATS_HPP
#include <cstdint>
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains some definitions to be used for core stats
* and scaling
*******************************************************************/
namespace DungeonDelver::GamePlay::Stats
{
	enum class StatType
	{
		NONE,
		STRENGTH,
		DEXTERITY,
		INTELLIGENCE,
		FAITH,
		VITALITY
	};

	enum class ScalingGrade
	{
		NONE	= 0,
		E		= 1,
		D		= 2,
		C		= 3,
		B		= 4,
		A		= 5,
		S		= 6

	};

	inline std::string StatTypeToString(const StatType& stat)
	{
		switch (stat)
		{
		case StatType::STRENGTH: return "Strength";
		case StatType::DEXTERITY: return "Dexterity";
		case StatType::INTELLIGENCE: return "Intelligence";
		case StatType::FAITH: return "Faith";
		case StatType::VITALITY: return "Vitality";
		default:
			return "None";
		}
	}
	
	inline StatType StringToStatType(const std::string& str)
	{
		if (str == "Strength") return StatType::STRENGTH;
		if (str == "Dexterity") return StatType::DEXTERITY;
		if (str == "Intelligence") return StatType::INTELLIGENCE;
		if (str == "Faith") return StatType::FAITH;
		if (str == "Vitality") return StatType::VITALITY;

		return StatType::NONE;
	}

	inline std::string ScalingGradeToString(const ScalingGrade& grade)
	{
		switch (grade)
		{
		case ScalingGrade::E: return "E";
		case ScalingGrade::D: return "D";
		case ScalingGrade::C: return "C";
		case ScalingGrade::B: return "B";
		case ScalingGrade::A: return "A";
		case ScalingGrade::S: return "S";
		default: 
			return "-";
		}
	}

	inline ScalingGrade StringToScalingGrade(const std::string& str)
	{
		if (str == "E") return ScalingGrade::E;
		if (str == "D") return ScalingGrade::D;
		if (str == "C") return ScalingGrade::C;
		if (str == "B") return ScalingGrade::B;
		if (str == "A") return ScalingGrade::A;
		if (str == "S") return ScalingGrade::S;

		return ScalingGrade::NONE;
	}
}

#endif
