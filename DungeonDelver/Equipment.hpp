#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP
#include <cstdint>
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains some definitions to be used for types of
* equipment and equipment slots
*******************************************************************/
namespace DungeonDelver::GamePlay::Items
{
	enum class EquipmentType
	{
		MISC,
		ARMOR,
		WEAPON,
		SHIELD
	};

	enum class EquipmentSlot : uint16_t
	{
		NONE		= 0,
		HEAD		= 1 << 0,
		CHEST		= 1 << 1,
		LEGS		= 1 << 2,
		HANDS		= 1 << 3,
		FEET		= 1 << 4,
		ONE_HAND	= 1 << 5,
		TWO_HAND	= 1 << 6,
		RANGED		= 1 << 7,
		OFF_HAND	= 1 << 8,
		RING_1		= 1 << 9,
		RING_2		= 1 << 10,
		NECK		= 1 << 11
	};

	//Enable bitwise operations
	inline EquipmentSlot operator | (EquipmentSlot a, EquipmentSlot b)
	{
		return static_cast<EquipmentSlot>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
	}

	inline bool HasSlot(EquipmentSlot value, EquipmentSlot slot)
	{
		return static_cast<uint16_t>(value) & static_cast<uint16_t>(slot);
	}
}
#endif