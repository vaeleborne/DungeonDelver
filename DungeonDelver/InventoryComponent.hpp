#ifndef INVENTORYCOMPONENT_HPP
#define INVENTORYCOMPONENT_HPP

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains a base interface for an inventory item
* I will be using a composite pattern, decorator, and factory 
* for our base inventory system
*******************************************************************/

#include <memory>
#include "ANSI_Colors.hpp"
#include "GameIO.hpp"
namespace DungeonDelver::GamePlay::Inventory
{
	class InventoryComponent
	{
	public:
		virtual ~InventoryComponent() = default;

		virtual void Add(std::shared_ptr<InventoryComponent>) {}

		virtual void Remove(std::shared_ptr<InventoryComponent>) {}

		virtual void Display(std::ostream& output, int indent = 0, bool inColor = false, const std::string& color = ANSI_WHITE) const = 0;

		virtual int GetWeight() const = 0;

		virtual int GetCost() const = 0;
	};
}

#endif