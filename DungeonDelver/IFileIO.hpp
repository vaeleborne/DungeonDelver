#ifndef IFILEIO_HPP
#define IFILEIO_HPP

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains an interface for file IO
*******************************************************************/
#include <string>

namespace DungeonDelver::System::IO
{
	class IFileIO
	{
	public:
		virtual ~IFileIO() = default;


		virtual bool WriteStringToFile(const std::string& fileName, const std::string& content, bool clearFileFirst) = 0;

		virtual bool ReadStringFromFile(const std::string& fileName, std::string& destinationStr) = 0;

		virtual bool WriteJSONToFile(const std::string& fileName, const std::string& content) = 0;

		virtual bool ReadStringFromJSONFile(const std::string& fileName, std::string& destinationStr) = 0;
	};
}

#endif