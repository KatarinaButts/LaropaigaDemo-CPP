#pragma once
#include <vector>


namespace Bengine2 {

	struct DirEntry {
		std::string path;
		bool isDirectory;
	};


	//static class (only has static methods)  [we only need one IOManager]
	class IOManager
	{
	public:
		//this function fills the vector with the data that they need
		//passes in the buffer by reference (because we for sure don't want to use a copy of the buffer in this case)
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);	//filepath, we're using a vector of chars buffer
		static bool readFileToBuffer(std::string filePath, std::string& buffer);	//filepath, we're using a string

		//gets all directory entries in the directory specified by path and stores in rvEntries
		//returns false if path is not a directory
		//static bool getDirectoryEntries(const char* path, std::vector<DirEntry>& rvEntries);
		//static bool makeDirectory(const char* path);
	};

}