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

unsigned int PathFolder::getFoldersize(std::string rootFolder, unsigned int size) { //default rootFolder = "", size = 0;
    if (rootFolder == "") {
        rootFolder = getPath();
    }

    const auto dir = std::filesystem::path{ rootFolder };

    for (std::filesystem::directory_entry const& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_directory()) {
            std::string path = entry.path().string();
            size = getFoldersize(path, size);
        }
        else if (entry.is_regular_file()) {
            size = size + entry.file_size();
        }

    }

    return size;
}

void PathFolder::deleteContents() {
    for (const auto& entry : std::filesystem::directory_iterator(getPath())) {
        std::filesystem::remove_all(entry.path());
    }
}