#include "Weapon.hpp";

using namespace DungeonDelver::GamePlay::Stats;

namespace DungeonDelver::GamePlay::Items
{
	void Weapon::Serialize(nlohmann::json& json) const
	{
		Item::Serialize(json);
		json["baseDamage"] = _baseDamage;

		for (const auto& [stat, grade] : _scaling.GetAllScaling())
		{
			json["scaling"][StatTypeToString(stat)] = ScalingGradeToString(grade);
		}
	}

	void Weapon::Deserialize(const nlohmann::json& json)
	{
		try
		{
			Item::Deserialize(json);
			_baseDamage = json.at("baseDamage").get<int>();

			if (json.contains("scaling"))
			{
				for (const auto& item : json["scaling"].items())
				{
					StatType stat = StringToStatType(item.key());
					ScalingGrade grade = StringToScalingGrade(item.value());
					_scaling.SetScaling(stat, grade);
				}
			}
		}
		catch (nlohmann::json::exception e)
		{
			throw e;
		}
		
	}

}