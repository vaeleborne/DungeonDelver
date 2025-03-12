#ifndef ISERIALIZABLE_HPP
#define ISERIALIZABLE_HPP
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an interface for a serializable class which
* needs to be able to save its data to json or load its data from
* json
*******************************************************************/

#include <string>
#include "json.hpp"

namespace DungeonDelver::System::IO
{
	class ISerializable
	{
	public:
		virtual ~ISerializable() = default;

		virtual void Serialize(nlohmann::json& json) const = 0;

		virtual void Deserialize(const nlohmann::json& json) = 0;
	};
}

#endif