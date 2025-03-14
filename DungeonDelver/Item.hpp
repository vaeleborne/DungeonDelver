#ifndef ITEM_HPP
#define ITEM_HPP
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an implementation of an Inventory Component,
* this component represents an item
*******************************************************************/
#include "InventoryComponent.hpp"
#include "ISerializable.hpp"
#include "Equipment.hpp"
#include <string>

namespace DungeonDelver::GamePlay::Items
{
	class Item : public  DungeonDelver::GamePlay::Inventory::InventoryComponent, public DungeonDelver::System::IO::ISerializable
	{
	protected: 
		std::string _name;
		float _weight;
		int _cost;
		EquipmentType _type;
		EquipmentSlot _slot;

	public:
		Item(const std::string& name, float weight, int cost);

		Item() {}

		virtual void Use();

		virtual std::string GetType();

		void Display(std::ostream& output, int indent = 0, bool inColor = false, const std::string& color = ANSI_WHITE) const override;

		int GetWeight() const override;

		int GetCost() const override;

		void Serialize(nlohmann::json& json) const override;

		void Deserialize(const nlohmann::json& json) override;
	};
}

#endif