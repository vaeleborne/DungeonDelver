#ifndef ISERIALIZABLE_HPP
#define ISERIALIZABLE_HPP
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an interface for a serializer using json
* we may want to convert to another format such as xml so we can
* implement different versions as needed
*******************************************************************/

#include <string>

namespace DungeonDelver::System::IO
{
	class ISerializer
	{
	public:
		virtual ~ISerializer() = default;

		virtual std::string ToJSON() const = 0;

		virtual void FromJSON(const std::string& jsonString) = 0;
	};
}

#endif