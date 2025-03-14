#include "Item.hpp"

namespace DungeonDelver::GamePlay::Items
{
	Item::Item(const std::string& name, float weight, int cost) : _name(name), _weight(weight), _cost(cost)
	{
		
	}

	void Item::Display(std::ostream& output, int indent, bool inColor, const std::string& color) const
	{
		DungeonDelver::System::IO::Write(output, std::string(indent, '-') + _name, true, inColor, color);
	}


	int Item::GetWeight() const
	{
		return _weight;
	}

	int Item::GetCost() const
	{
		return _cost;
	}

	void Item::Serialize(nlohmann::json& json) const
	{
		json =
		{
			{"type", "item"},
			{"name", _name},
			{"weight", _weight},
			{"cost", _cost}
		};
	}

	void Item::Deserialize(const nlohmann::json& json)
	{
		try
		{
			_name = json.at("name").get< std::string > ();
			_weight = json.at("weight").get<float>();
			_cost = json.at("cost").get<int>();
		}
		catch (nlohmann::json::exception e)
		{
			std::cerr << "Error Deserializing Item: " << e.what() << std::endl;
			throw e;
		}
	}
}

