#ifndef INVENTORYCONTAINER_HPP
#define INVENTORYCONTAINER_HPP

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an implementation of an Inventory Component,
* this component represents a container of of components
*******************************************************************/

#include "InventoryComponent.hpp"
#include "Item.hpp"
#include "ISerializable.hpp"
#include "InventoryFactory.hpp"

namespace DungeonDelver::GamePlay::Inventory
{

	class InventoryContainer : public InventoryComponent, public DungeonDelver::System::IO::ISerializable
	{
	private:
		std::string _name;
		std::vector<std::shared_ptr<InventoryComponent>> _items;

	public:
		InventoryContainer(const std::string& name);

		InventoryContainer(){}

		void Add(std::shared_ptr<InventoryComponent> item) override;

		void Remove(std::shared_ptr<InventoryComponent> item) override;

		void Display(std::ostream& output, int indent = 0, bool inColor = false, const std::string& color = ANSI_WHITE) const override;

		int GetWeight() const override;

		int GetCost() const override;

		void Serialize(nlohmann::json& json) const override;

		void Deserialize(const nlohmann::json& json) override;
	};
}

#endif