#pragma once
#include <iostream>
#include <Shlobj.h>
#include <filesystem>
typedef unsigned long long ullong;

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
	ullong getFoldersize(std::string rootFolder = "", ullong size = 0);
	bool deleteContents();
};