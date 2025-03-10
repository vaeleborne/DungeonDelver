#include "Item.hpp"

namespace DungeonDelver::GamePlay::Inventory
{
	Item::Item(const std::string& name, float weight, int cost) : _name(name), _weight(weight), _cost(cost)
	{
		
	}

	void Item::Display(std::ostream& output, int indent, bool inColor = false, const std::string& color = ANSI_WHITE) const
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
}

