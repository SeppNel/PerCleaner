#pragma once
#include <iostream>
#include <Shlobj.h>

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
};