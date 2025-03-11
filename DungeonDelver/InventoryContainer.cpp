#include "InventoryContainer.hpp"

namespace DungeonDelver::GamePlay::Inventory
{
	InventoryContainer::InventoryContainer(const std::string& name) : _name(name) {}

	void InventoryContainer::Add(std::shared_ptr<InventoryComponent> item)
	{
		throw "Not Implemented";
	}

	void InventoryContainer::Remove(std::shared_ptr<InventoryComponent> item)
	{
		throw "Not Implemented";
	}

	void InventoryContainer::Display(std::ostream& output, int indent = 0, bool inColor = false, const std::string& color = ANSI_WHITE) const
	{
		throw "Not Implemented";
	}

	int InventoryContainer::GetWeight() const
	{
		throw "Not Implemented";
	}

	int InventoryContainer::GetCost() const
	{
		throw "Not Implemented";
	}

	std::string InventoryContainer::ToJSON() const
	{
		throw "Not Implemented";
	}

	void InventoryContainer::FromJSON(const std::string& jsonString)
	{
		throw "Not Implemented";
	}
}