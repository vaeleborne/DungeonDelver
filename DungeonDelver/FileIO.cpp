#include "FileIO.hpp"

namespace DungeonDelver::System::IO
{
    bool FileIO::WriteStringToFile(const std::string& fileName, const std::string& content, bool clearFileFirst)
    {
		std::ofstream file;

		if (clearFileFirst == false)
			file.open(fileName, std::ios::app);
		else
			file.open(fileName);

		if (!file.is_open())
		{
			return false;
		}

		file << content;
		file.close();

        return true;
    }

    bool FileIO::ReadStringFromFile(const std::string& fileName, std::string& destinationStr)
    {
		std::ifstream file(fileName);

		if (!file.is_open())
		{
			return false;
		}

		//If we get here, the file is open
		std::string line;
		std::stringstream contents;
		while (std::getline(file, line))
		{
			contents << line << '\n';
		}

		file.close();

		destinationStr = contents.str();
        return true;
    }
}