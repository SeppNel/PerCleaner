#include "PathFolder.h"

std::string PathFolder::getPath() {
	return path_;
}

bool PathFolder::isLog() {
	return is_log_;
}

std::string PathFolder::getUserFolderPath() {
	std::string path;
	CHAR buf[MAX_PATH + 100];
	SHGetSpecialFolderPathA(0, buf, CSIDL_PROFILE, FALSE);
	path = buf;
	return path + "\\";
}