#ifndef ISCALING_HPP
#define ISCALING_HPP
#include "CoreStats.hpp"
#include <unordered_map>

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an interface for a scaling class, to be 
* implemented for various scaling concrete classes like a weapon 
* scaler and armor scaler
*******************************************************************/
namespace DungeonDelver::GamePlay::Stats
{
	class IScaling
	{
	public:
		virtual ~IScaling() = default;

		virtual void SetScaling(StatType stat, ScalingGrade grade) = 0;
		virtual ScalingGrade GetScaling(StatType stat) const = 0;
		virtual const std::unordered_map < StatType, ScalingGrade>& GetAllScaling() const = 0;
	};
}

#endif