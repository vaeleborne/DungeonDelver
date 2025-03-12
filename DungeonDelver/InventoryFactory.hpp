#ifndef INVENTORYFACTORY_HPP
#define INVENTORYFACTORY_HPP
#include "Item.hpp"
#include "InventoryContainer.hpp"
#include <memory>
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains declaration of a factory pattern to be 
* used for creating pointers to inventory related objects that 
* are serializable
*******************************************************************/
namespace DungeonDelver::GamePlay::Inventory
{

	class InventoryFactory
	{
	public:
		static std::shared_ptr<InventoryComponent> CreateInventoryComponent(const nlohmann::json& json);
	};

}


#endif