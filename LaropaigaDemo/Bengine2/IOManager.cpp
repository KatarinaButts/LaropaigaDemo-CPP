#include "IOManager.h"

#include <filesystem>
#include <fstream>

//Namespace alias
//namespace fs = std::filesystem;

namespace Bengine2 {

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
		std::ifstream file(filePath, std::ios::binary);		//flag is tell the ifstream that we are reading in binary data/format
		//error checking
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}
		//read the contents of the file into the buffer (assuming it has a size of 0 initially)

		//how to determine how big a file is: seekg, tellg
		//seek to the end
		file.seekg(0, std::ios::end);	//byte offset, where to seek until

		//get the file size
		int fileSize = file.tellg();	//returns an integer which tells us how many bytes are before the current location (ie how many we have passed)

		//seek back to the beginning, so we can read what is actually in the file
		file.seekg(0, std::ios::beg);
		//now we are back at the beginning of the file

		//reduce the file size by any header bytes that might be present/lingering
		fileSize -= file.tellg(); //in case there is a header at the beginning of the file. This tells the program to skip that header (skips the initial potential header bytes).

		buffer.resize(fileSize);
		//(char*)& pretends that it's a buffer of chars (even though this is a actually a buffer of unsigned chars)
		file.read((char*)&(buffer[0]), fileSize);	//just reads a number of bytes into a buffer (buffer location {[char *]: for our example we need to find the initial address of buffer of char vectors and this is how to do that} <- this will give us our c_str, how many bytes we want to read)

		//close the file as a precaution
		file.close();
		return true; //since we successfully opened the file
	}

	bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer) {
		std::ifstream file(filePath, std::ios::binary);		//flag is tell the ifstream that we are reading in binary data/format
		//error checking
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}
		//read the contents of the file into the buffer (assuming it has a size of 0 initially)

		//how to determine how big a file is: seekg, tellg
		//seek to the end
		file.seekg(0, std::ios::end);	//byte offset, where to seek until

		//get the file size
		int fileSize = (unsigned int)file.tellg();	//returns an integer which tells us how many bytes are before the current location (ie how many we have passed)

		//seek back to the beginning, so we can read what is actually in the file
		file.seekg(0, std::ios::beg);
		//now we are back at the beginning of the file

		//reduce the file size by any header bytes that might be present/lingering
		fileSize -= file.tellg(); //in case there is a header at the beginning of the file. This tells the program to skip that header (skips the initial potential header bytes).

		buffer.resize(fileSize);
		//(char*)& pretends that it's a buffer of chars (even though this is a actually a buffer of unsigned chars)
		file.read((char*)&(buffer[0]), fileSize);	//just reads a number of bytes into a buffer (buffer location {[char *]: for our example we need to find the initial address of buffer of char vectors and this is how to do that} <- this will give us our c_str, how many bytes we want to read)

		//close the file as a precaution
		file.close();
		return true; //since we successfully opened the file
	}

	/*
	bool IOManager::getDirectoryEntries(const char* path, std::vector<DirEntry>& rvEntries) {
		auto dpath = fs::path(path);
		// Must be directory
		if (!fs::is_directory(dpath)) return false;

		for (auto it = fs::directory_iterator(dpath); it != fs::directory_iterator(); ++it) {
			rvEntries.emplace_back();
			rvEntries.back().path = it->path().string();
			if (is_directory(it->path())) {
				rvEntries.back().isDirectory = true;
			}
			else {
				rvEntries.back().isDirectory = false;
			}
		}
		return true;
	}

	bool IOManager::makeDirectory(const char* path) {
		return fs::create_directory(fs::path(path));
	}

	*/

}