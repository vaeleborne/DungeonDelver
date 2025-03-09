#ifndef FILEIO_HPP
#define FILEIO_HPP

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains the declaration of an implementation of our
* FileIO interface
*******************************************************************/

#include "IFileIO.hpp"

namespace DungeonDelver::System::IO
{
	class FileIO : public IFileIO
	{
		bool WriteStringToFile(const std::string& fileName, const std::string& content) override;

		bool ReadStringFromFile(const std::string& fileName, std::string& destinationStr) override;


	};
}

#endif