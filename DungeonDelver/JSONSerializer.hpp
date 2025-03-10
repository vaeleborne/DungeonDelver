#ifndef JSONSERIALIZER_HPP
#define JSONSERIALIZER_HPP

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains a template implementation of our serializer
*******************************************************************/

#include "ISerializable.hpp"
#include "json.hpp"

namespace DungeonDelver::System::IO
{
	template<typename T>
	class JSONSerializer : public ISerializable
	{
	private:
		T& _object;

	public:
		explicit JSONSerializer(const T& object) : _object(object) {}

		std::string ToJSON() const override
		{
			nlohmann::json json;
			_object.Serialize(json);
			return json.dump();
		}

		void FromJSON(const std::string& jsonString) override
		{
			nlohmann::json json = nlohmann::json::parse(jsonString);
			_object.Deserialize(json);
		}
	};
}
#endif