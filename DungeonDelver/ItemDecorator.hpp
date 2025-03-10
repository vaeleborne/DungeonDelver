#ifndef ITEMDECORATOR_HPP
#define ITEMDECORATOR_HPP

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: This will be the base for our decorator for 
* inventory components, can extend this for varied displays 
* and weights, costs, etc, such as for an enchanted item
*******************************************************************/

#include "InventoryComponent.hpp"

namespace DungeonDelver::GamePlay::Inventory
{
	class ItemDecorator : public InventoryComponent
	{
	protected:
		std::shared_ptr<InventoryComponent> _component;

	public:
		ItemDecorator(std::shared_ptr<InventoryComponent> item);

		void Display(std::ostream& output, int indent, bool inColor = false, const std::string& color = ANSI_WHITE) const override;

		int GetWeight() const override;

	};
}

#endif