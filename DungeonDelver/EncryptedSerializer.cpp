#include "EncryptedSerializer.hpp"

namespace DungeonDelver::System::IO
{

	EncryptedSerializer::EncryptedSerializer(ISerializer& serializer, const std::string& key) : _serializer(serializer), _key(key) {}

	std::string EncryptedSerializer::Encrypt(const std::string& data) const
	{
		std::string encrypted = data;

		for (size_t i = 0; i < encrypted.size(); i++)
		{
			encrypted[i] ^= _key[i % _key.size()];
		}

		return encrypted;
	}

	std::string EncryptedSerializer::Decrypt(const std::string& data) const
	{
		return Encrypt(data);	//Using xor so we can do this
	}

	std::string EncryptedSerializer::ToJSON() const
	{
		std::string data = _serializer.ToJSON();
		return Encrypt(data);
	}

	void EncryptedSerializer::FromJSON(const std::string& encryptedJsonString)
	{
		std::string decryptedData = Decrypt(encryptedJsonString);
		_serializer.FromJSON(encryptedJsonString);
	}

}
