#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Item.hpp"
#include "WeaponScaling.hpp"
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an item implementation representing a 
* weapon. This can be one handed, two handed, or ranged, or really
* anything else if we extend Equipment types
*******************************************************************/
namespace DungeonDelver::GamePlay::Items
{
	class Weapon : public  Item
	{
	protected:
		int _baseDamage;
		DungeonDelver::GamePlay::Stats::WeaponScaling _scaling;

	public:
		Weapon(const std::string& name, float weight, int cost, int baseDamage,EquipmentType weaponType, EquipmentSlot weaponSlot);
		Weapon();

		void Use() override;

		void SetScaling(DungeonDelver::GamePlay::Stats::StatType stat, DungeonDelver::GamePlay::Stats::ScalingGrade grade);

		int CalculateBonusDamage(const std::unordered_map< DungeonDelver::GamePlay::Stats::StatType, int>& playerStats) const;

		int GetTotalDamage(const std::unordered_map< DungeonDelver::GamePlay::Stats::StatType, int>& playerStats) const;

		std::string GetType() override;

		void Serialize(nlohmann::json& json) const override;

		void Deserialize(const nlohmann::json& json) override;
	};
}

#endif