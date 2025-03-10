#ifndef ISERIALIZABLE_HPP
#define ISERIALIZABLE_HPP
/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an interface for a serializable class which
* will be used with a decorator pattern for data saving and loading
*******************************************************************/

#include <string>

namespace DungeonDelver::System::IO
{
	class ISerializable
	{
	public:
		virtual ~ISerializable() = default;

		virtual std::string ToJSON() const = 0;

		virtual void FromJSON(const std::string& jsonString) = 0;
	};
}

#endif