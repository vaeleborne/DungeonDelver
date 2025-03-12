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
#include <memory>


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

	MockObject(std::string name, int value) : name(name), value(value)
	{
		objects.push_back("Object 1");
		objects.push_back("Object 2");
		objects.push_back("Object 3");
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

	void operator=(const MockObject& other)
	{
		this->name = other.name;
		this->value = other.value;
		this->objects = std::vector<std::string>(other.objects);
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
			name = "invalid";
			value = 0;
			objects.clear();
			throw e;
		}
	}
};

//TODO: Implement a Compounding mock object class (stores pointers to other objects) to make sure that it can serialize those properly
class MockObjectContainer : public inv::ISerializable
{
public:
	std::string name;
	std::vector<MockObject> objects;
	std::shared_ptr<MockObject> sharedPtrObject;
	std::unique_ptr<MockObject> uniquePtrObject;
	MockObject* oldPtrObject;

	MockObjectContainer()
	{
		name = "Mock Container";
		objects.push_back(MockObject());
		objects.push_back(MockObject("A different Object", 3));
		objects.push_back(MockObject("Yet another Object", 5));

		sharedPtrObject = std::make_shared<MockObject>(MockObject("Shared Pointer Object", 6));
		uniquePtrObject = std::make_unique<MockObject>(MockObject("Unique Pointer Object", 102));
		oldPtrObject = new MockObject("Old, bad pointer Object", 9);
	}

	MockObjectContainer(std::string n, std::vector<MockObject> o, MockObject shared, MockObject unique, MockObject old)
	{
		name = n;
		objects = std::vector<MockObject>(o);

		sharedPtrObject = std::make_shared<MockObject>(shared);
		uniquePtrObject = std::make_unique<MockObject>(unique);

		oldPtrObject = new MockObject();
		*oldPtrObject = old;
	}

	~MockObjectContainer()
	{
		delete oldPtrObject;
	}
	
	bool operator==(const MockObjectContainer& other) const
	{
		if (this->name != other.name || *this->sharedPtrObject != *other.sharedPtrObject  || *this->oldPtrObject != *other.oldPtrObject || *this->uniquePtrObject != *other.uniquePtrObject)
			return false;

		if (this->objects.size() != other.objects.size())
			return false;

		for (int i = 0; i < this->objects.size(); i++)
		{
			if (this->objects[i] != other.objects[i])
				return false;
		}

		return true;
	}

	void operator=(const MockObjectContainer& other)
	{
		this->name = other.name;
		*this->sharedPtrObject = *other.sharedPtrObject;
		*this->uniquePtrObject = *other.uniquePtrObject;
		*this->oldPtrObject = *other.oldPtrObject;

		objects.clear();
		for (MockObject obj : other.objects)
		{
			objects.push_back(obj);
		}
	}

	void Serialize(nlohmann::json& json) const override
	{
		json["type"] = "Mock Container";
		json["name"] = name;

		if (sharedPtrObject != nullptr)
		{
			sharedPtrObject->Serialize(json["sharedPtr"]);
		}
		else
		{
			json["sharedPtr"] = nullptr;
		}

		if (uniquePtrObject != nullptr)
		{
			uniquePtrObject->Serialize(json["uniquePtr"]);
		}
		else
		{
			json["uniquePtr"] = nullptr;
		}

		if (oldPtrObject != nullptr)
		{
			oldPtrObject->Serialize(json["oldPtr"]);
		}
		else
		{
			json["oldPtr"] = nullptr;
		}

		json["objects"] = nlohmann::json::array();

		for (const auto& obj : objects)
		{
			nlohmann::json mockJson;
			obj.Serialize(mockJson);
			json["objects"].push_back(mockJson);
		}
	}

	void Deserialize(const nlohmann::json& json) override
	{
		try
		{
			name = json.at("name").get<std::string>();

			if (!json.at("sharedPtr").is_null())
			{
				sharedPtrObject = std::make_shared<MockObject>();
				sharedPtrObject->Deserialize(json["sharedPtr"]);
			}
			else
			{
				sharedPtrObject = nullptr;
			}

			if (!json.at("uniquePtr").is_null())
			{
				uniquePtrObject = std::make_unique<MockObject>();
				uniquePtrObject->Deserialize(json["uniquePtr"]);
			}
			else
			{
				uniquePtrObject = nullptr;
			}

			if (!json.at("oldPtr").is_null())
			{
				if (oldPtrObject != nullptr)
				{
					oldPtrObject->Deserialize(json["oldPtr"]);
				}
				else
				{
					oldPtrObject = new MockObject();
					oldPtrObject->Deserialize(json["oldPtr"]);
				}
			}
			else
			{
				if (oldPtrObject != nullptr)
				{
					delete oldPtrObject;
				}
				oldPtrObject = nullptr;
			}

			objects.clear();
			for (const auto& mockJson : json.at("objects"))
			{
				MockObject obj;
				obj.Deserialize(mockJson);
				objects.push_back(obj);
			}
		}
		catch (nlohmann::json::exception e)
		{
			throw e;
		}
		

	}
};


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

TEST(SerializationTest, DeserializeThrowsErrorWithEmptyJson)
{
	MockObject obj;
	nlohmann::json json;
	EXPECT_THROW(obj.Deserialize(json), nlohmann::json::exception);
}

TEST(SerializationTest, DeserializeThrowsErrorWithInvalidJsonValues)
{
	MockObject obj;
	nlohmann::json json = 
	{
		{"junkData", 5},
		{"more data", "na"}
	};
	EXPECT_THROW(obj.Deserialize(json), nlohmann::json::exception);
}

TEST(SerializationTest, DeserializeContainerWithPointersAndVectorGetsExpectedValues)
{
	std::string name = "Serialize Test!";
	std::vector<std::string> strings;
	strings.push_back("Object 4");
	strings.push_back("Object 5");
	strings.push_back("Object 6");

	MockObject sharedObj("Shared Obj", 20);
	MockObject uniqueObj("Unique Obj", 3, strings);
	MockObject oldObj("Old Obj", 5);

	MockObject obj1("Object 1", 4);
	MockObject obj2("Object 2", 6);
	MockObject obj3("Object 3", 7);

	std::vector<MockObject> objects;
	objects.push_back(obj1);
	objects.push_back(obj2);
	objects.push_back(obj3);

	MockObjectContainer serializeTestObj(name, objects, sharedObj, uniqueObj, oldObj);
	MockObjectContainer testerObj;


	EXPECT_FALSE(serializeTestObj == testerObj);

	nlohmann::json j;
	serializeTestObj.Serialize(j);
	testerObj.Deserialize(j);
	EXPECT_TRUE(serializeTestObj == testerObj);
}

TEST(SerializationTest, SerializerWorksAsExpected)
{
	MockObject testObj;
	
	inv::JSONSerializer<MockObject> serializer(testObj);

	std::string jsonStr = serializer.ToJSON();

	std::string expectedStr = "{\"name\":\"Mock Object\",\"objects\":[\"Object 1\",\"Object 2\",\"Object 3\"],\"type\":\"MockObject\",\"value\":1}";

	EXPECT_EQ(expectedStr, jsonStr);
}

TEST(SerializationTest, DeserializerWorksAsExpected)
{
	std::vector<std::string> strings;
	strings.push_back("Object 4");
	strings.push_back("Object 5");
	strings.push_back("Object 6");

	nlohmann::json json;

	MockObject objToSerialize("Deserialize Test!", 42, strings);
	MockObject objToDeserialize;

	EXPECT_FALSE(objToSerialize == objToDeserialize);

	inv::JSONSerializer<MockObject> serializer(objToSerialize);

	inv::JSONSerializer<MockObject> otherSerializer(objToDeserialize);

	otherSerializer.FromJSON(serializer.ToJSON());

	EXPECT_TRUE(objToSerialize == objToDeserialize);
}

