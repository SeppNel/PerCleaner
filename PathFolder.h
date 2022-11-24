#pragma once
#include <iostream>
#include <Shlobj.h>
#include <filesystem>

class PathFolder
{
private:
	std::string path_;
	bool is_log_;
public:
	PathFolder(std::string path, bool is_log = false) {
		path_ = path;
		is_log_ = is_log;
	}

	std::string getPath();
	bool isLog();
	static std::string getUserFolderPath();
	unsigned int getFoldersize(std::string rootFolder = "", unsigned int size = 0);
	void deleteContents();
};