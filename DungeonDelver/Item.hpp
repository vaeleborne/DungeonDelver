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
#include <string>

namespace DungeonDelver::GamePlay::Inventory
{
	class Item : public InventoryComponent, public DungeonDelver::System::IO::ISerializable
	{
	protected: 
		std::string _name;
		float _weight;
		int _cost;

	public:
		Item(const std::string& name, float weight, int cost);

		Item() {}

		void Display(std::ostream& output, int indent = 0, bool inColor = false, const std::string& color = ANSI_WHITE) const override;

		int GetWeight() const override;

		int GetCost() const override;

		void Serialize(nlohmann::json& json) const override;

		void Deserialize(const nlohmann::json& json) override;
	};
}

#endif