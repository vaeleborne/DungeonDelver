#ifndef ENCRYPTEDSERIALIZER_HPP
#define ENCRYPTEDSERIALIZER_HPP

#include "ISerializer.hpp"

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an class that can decorate a serializer to
* add basic encryption. Note, we will just use xor encryption here
* and the key isn't exactly secret, but this is okay here as this 
* is for demonstrative purposes, we could always modify the 
* encryption methods here easily, or add a different decorator for
* more secure encryption like AES!
*******************************************************************/

namespace DungeonDelver::System::IO
{
	class EncryptedSerializer : public ISerializer
	{
	private:
		ISerializer& _serializer;
		const std::string& _key;

		std::string Encrypt(const std::string& data) const;
		std::string Decrypt(const std::string& data) const;

	public:
		explicit EncryptedSerializer(ISerializer& serializer, const std::string& key);

		std::string ToJSON() const override;

		void FromJSON(const std::string& encryptedJsonString) override;
	};
}

#endif