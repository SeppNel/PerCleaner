#pragma once
#include <iostream>
#include <atlstr.h>
#include <shlobj.h>

class Folder
{
private:
	std::string path_;
	bool is_log_;
	bool is_from_user_;
public:
	Folder(std::string path) {
		path_ = path;
		is_log_ = false;
		is_from_user_ = false;
	}

	Folder(std::string path, bool is_log, bool is_from_user) {
		path_ = path;
		is_log_ = is_log;
		is_from_user_ = is_from_user;
	}

	std::string getPath();
	bool isLog();
	bool isFromUser();

	static std::string getUserPath();
};