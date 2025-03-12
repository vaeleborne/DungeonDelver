/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: This file contains comprhensive unit testing for
* the DungeonDelver library's serialization related functions
*******************************************************************/

#include "pch.h"
#include <sstream>
#include "../DungeonDelver/ISerializable.hpp"
#include "../DungeonDelver/JSONSerializer.hpp"
#include <vector>


namespace inv = DungeonDelver::System::IO;

const std::string MOCK_NAME = "Mock Object";
const int MOCK_VALUE = 1;

//Basic mock class of a serializable object with some different data types for testing
class MockObject : public DungeonDelver::System::IO::ISerializable
{
public:
	std::string name;
	int value;
	std::vector<std::string> objects;

	MockObject() : name(MOCK_NAME), value(MOCK_VALUE) 
	{
		objects.push_back("Object 1");
		objects.push_back("Object 2");
		objects.push_back("Object 3");
	}

	MockObject(std::string name, int value, std::vector<std::string> items) : name(name), value(value), objects(items)
	{
	}

	bool operator==(const MockObject& other) const
	{
		if (this->name != other.name || this->value != other.value)
			return false;

		if (this->objects.size() != other.objects.size())
		{
			return false;
		}

		for (int i = 0; i < this->objects.size(); i++)
		{
			if (this->objects[i] != other.objects[i])
			{
				return false;
			}
		}

		return true;
	}

	void Serialize(nlohmann::json& json) const override
	{
		json =
		{
			{"type", "MockObject"},
			{"name", name},
			{"value", value},
			{"objects", objects}
		};
	}

	void Deserialize(const nlohmann::json& json) override
	{
		try
		{
			name = json.at("name").get<std::string>();
			value = json.at("value").get<int>();
			objects = json.at("objects").get<std::vector<std::string>>();
		}
		catch(const nlohmann::json::exception& e)
		{
			std::cerr << "Item deserialization failed!: " << e.what() << std::endl;
			name = "invalid";
			value = 0;
			objects.clear();
		}
	}
};

//TODO: Implement a Compounding mock object class (stores pointers to other objects) to make sure that it can serialize those properly


TEST(SerializationTest, SerializeGetsExpectedJsonValues)
{
	std::vector<std::string> strings;
	strings.push_back("Object 1");
	strings.push_back("Object 2");
	strings.push_back("Object 3");

	nlohmann::json expected =
	{
		{ "type", "MockObject" },
		{ "name", MOCK_NAME },
		{ "value", MOCK_VALUE },
		{ "objects", strings }
	};

	nlohmann::json actual;

	MockObject testObj;

	testObj.Serialize(actual);

	EXPECT_EQ(expected, actual);
}

TEST(SerializationTest, DeserializeGetsExpectedJsonValues)
{
	std::vector<std::string> strings;
	strings.push_back("Object 4");
	strings.push_back("Object 5");
	strings.push_back("Object 6");

	nlohmann::json json;

	MockObject objToSerialize("Deserialize Test!", 42, strings);
	MockObject objToDeserialize;

	EXPECT_FALSE(objToSerialize == objToDeserialize);

	objToSerialize.Serialize(json);
	objToDeserialize.Deserialize(json);

	EXPECT_TRUE(objToSerialize == objToDeserialize);
}

