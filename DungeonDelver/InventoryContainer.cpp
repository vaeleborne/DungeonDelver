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

	void InventoryContainer::Display(std::ostream& output, int indent, bool inColor, const std::string& color) const
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

	void InventoryContainer::Serialize(nlohmann::json& json) const
	{
		json["type"] = "inventory container";
		json["name"] = _name;

		json["items"] = nlohmann::json::array();

		for (const auto ptr : _items)
		{
			nlohmann::json tempJson;
			if (ptr == nullptr)
			{
				json["items"].push_back(nullptr);
			}
			else
			{
				ptr->Serialize(tempJson);
				json["items"].push_back(tempJson);
			}
		}
	}

	void InventoryContainer::Deserialize(const nlohmann::json& json)
	{
		try
		{
			_name = json.at("name").get<std::string>();
			_items.clear();
			for (const auto& itemJson : json.at("items"))
			{
				if (!itemJson.is_null())
				{
					_items.push_back(InventoryFactory::CreateInventoryComponent(itemJson));
				}
				else
				{
					_items.push_back(nullptr);
				}
			}
		}
		catch (nlohmann::json::exception e)
		{
			std::cerr << "Error Deserializing Item: " << e.what() << std::endl;
			throw e;
		}
	}

}