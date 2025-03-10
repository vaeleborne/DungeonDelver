#ifndef FILEIO_HPP
#define FILEIO_HPP

/*******************************************************************
* AUTHOR: Dylan Morgan
*
* DESCRIPTION: Contains the declaration of an implementation of our
* FileIO interface
*******************************************************************/

#include "IFileIO.hpp"
#include <fstream>
#include <sstream>

namespace DungeonDelver::System::IO
{
	class FileIO : public IFileIO
	{
		/// <summary>
	/// Writes a string to a file, can set clearFileFirst to false to simply append to the file
	/// </summary>
	/// <param name="fileName">
	/// The path to our file with its name
	/// </param>
	/// <param name="content">
	/// What to write to the file
	/// </param>
	/// <param name="clearFileFirst">
	/// If we should clear the file before writing to it, defaults to true
	/// </param>
	///<returns>
	/// True if we could write successfully
	/// </returns>
		bool WriteStringToFile(const std::string& fileName, const std::string& content, bool clearFileFirst = true) override;

		/// <summary>
		/// Reads the contents of a file into a string, each line will have a newline character
		/// </summary>
		/// <param name="fileName">
		/// The path to our file with its name
		/// </param>
		/// <param name="destinationStr">
		/// The string we will write to
		/// </param>
		/// <returns>
		/// True if we could read successfully
		/// </returns>
		bool ReadStringFromFile(const std::string& fileName, std::string& destinationStr) override;
	};
}

#endif