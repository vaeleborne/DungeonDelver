#ifndef WEAPONSCALING_HPP
#define WEAPONSCALING_HPP
#include "IScaling.hpp"
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an implementation of IScaling to be used 
* for scaling a weapon
*******************************************************************/
namespace DungeonDelver::GamePlay::Stats
{
	class WeaponScaling : IScaling
	{
	private:
		std::unordered_map<StatType, ScalingGrade> _scaling;
	public:
		void SetScaling(StatType stat, ScalingGrade grade) override;

		ScalingGrade GetScaling(StatType stat) const override;

		const std::unordered_map<StatType, ScalingGrade>& GetAllScaling() const override;
	};
}
#endif