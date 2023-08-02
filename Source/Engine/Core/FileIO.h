#pragma once
#include <filesystem>
#include <string>

namespace MEN
{
	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& filePath);

	bool setFilePath(const std::filesystem::path& path);
	std::string getFilePath(const std::filesystem::path& path);

	bool fileExists(const std::filesystem::path& filePath);
	bool getFileSize(const std::filesystem::path& filePath, size_t& fileSize);
	bool readFile(const std::filesystem::path& filePath, std::string& buffer); // buffer: A block of data


}