#include "InventoryFactory.hpp"
#include "Weapon.hpp"
namespace DungeonDelver::GamePlay::Inventory
{
	std::shared_ptr<InventoryComponent> InventoryFactory::CreateInventoryComponent(const nlohmann::json& json)
	{
		std::string type = json.at("type").get<std::string>();

		if (type == "item")
		{
			auto item = std::make_shared<DungeonDelver::GamePlay::Items::Item>();
			item->Deserialize(json);
			return item;
		}
		else if (type == "inventory container")
		{
			auto item = std::make_shared<InventoryContainer>();
			item->Deserialize(json);
			return item;
		}
		else if (type == "weapon")
		{
			auto weapon = std::make_shared<DungeonDelver::GamePlay::Items::Weapon>();
			weapon->Deserialize(json);
			return weapon;
		}
		//TODO: Add Future Types Here

		return nullptr;
	}
}