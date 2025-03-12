#include "InventoryContainer.hpp"

namespace DungeonDelver::GamePlay::Inventory
{
	InventoryContainer::InventoryContainer(const std::string& name) : _name(name) {}

	void InventoryContainer::Add(std::shared_ptr<InventoryComponent> item)
	{
		_items.push_back(item);
	}

	void InventoryContainer::Remove(std::shared_ptr<InventoryComponent> item)
	{
		auto it = std::find(_items.begin(), _items.end(), item);
		if (it != _items.end())
		{
			_items.erase(it);
		}
	}

	void InventoryContainer::Display(std::ostream& output, int indent, bool inColor, const std::string& color) const
	{
		throw "Not Implemented";
	}

	int InventoryContainer::GetWeight() const
	{
		float totalWeight = 0;
		for (auto item : _items)
		{
			totalWeight += item->GetWeight();
		}

		return totalWeight;
	}

	int InventoryContainer::GetCost() const
	{
		int totalCost = 0;

		for (auto item : _items)
		{
			totalCost += item->GetCost();
		}
		
		return totalCost;
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
				auto serializable = std::dynamic_pointer_cast<DungeonDelver::System::IO::ISerializable>(ptr);
				if (!serializable)
				{
					throw std::runtime_error("Could Not Serialize Item, it is not a Serializable!");
				}

				serializable->Serialize(tempJson);
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