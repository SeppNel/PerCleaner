#include <iostream>
#include <yaml-cpp/yaml.h>
#include "PathFolder.h"
#include <vector>
#include <filesystem>

std::string readable_fs(float size) {
    int i = 0;
    const std::string units[] = { "B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
    while (size > 1024) {
        size /= 1024;
        i++;
    }

    std::string s = std::format("{:.2f}", size);

    return s +  units[i];
}

std::string resolvePath(std::string path)
{
    std::string parent = path.substr(0, path.find('*'));
    std::string tmp = path.substr(path.find('*'));
    std::string child = tmp.substr(0, tmp.find('\\'));
    std::string extra = tmp.substr(tmp.find('\\'));

    WIN32_FIND_DATAA data;
    HANDLE hFind;

    std::string searchPath = parent + child;

    hFind = FindFirstFileA(searchPath.c_str(), &data);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return "0";
    }
    else
    {
        FindClose(hFind);
    }

    return parent + data.cFileName + extra;
}


std::vector<PathFolder> readFolders() {
    YAML::Node file = YAML::LoadFile("folders.yaml");
    std::vector<PathFolder> folders;
    std::string user = PathFolder::getUserFolderPath();

    for (int i = 0; i < file["Absolute"]["General"].size(); i++)
    {
        std::string path = file["Absolute"]["General"][i].as<std::string>();
        if (std::filesystem::exists(path)) {
            folders.push_back(PathFolder(path));
        }
    }

    for (int i = 0; i < file["Absolute"]["Logs"].size(); i++)
    {
        std::string path = file["Absolute"]["Logs"][i].as<std::string>();
        if (std::filesystem::exists(path)) {
            folders.push_back(PathFolder(path, true));
        }
    }

    for (int i = 0; i < file["User"]["General"].size(); i++)
    {
        std::string path = file["User"]["General"][i].as<std::string>();
        
        if (path.find('*') != std::string::npos) {
            path = resolvePath(user + path);
            if (std::filesystem::exists(path)) {
                folders.push_back(PathFolder(path));
            }
        }
        else {
            if (std::filesystem::exists(user + path)) {
                folders.push_back(PathFolder(user + path));
            }
        }
    }

    for (int i = 0; i < file["User"]["Logs"].size(); i++)
    {
        std::string path = file["User"]["Logs"][i].as<std::string>();

        if (path.find('*') != std::string::npos) {
            path = resolvePath(user + path);
            if (std::filesystem::exists(path)) {
                folders.push_back(PathFolder(path, true));
            }
        }
        else {
            if (std::filesystem::exists(user + path)) {
                folders.push_back(PathFolder(user + path, true));
            }
        }
    }

    return folders;
}


char menu() {
    std::cout << "What do you want to delete?" << std::endl;
    std::cout << "[E] Everything | [C] Cache Only | [L] Logs Only | [S] Scan Only (default)" << std::endl;

    char input;
    std::cin.get(input);

    return toupper(input);
}

void scanOnly(std::vector<PathFolder> folders) {
    unsigned int sumCache = 0;
    unsigned int sumLogs = 0;
    for (int i = 0; i < folders.size(); i++) {
        if (folders[i].isLog()) {
            sumLogs = sumLogs + folders[i].getFoldersize();
        }
        else {
            sumCache = sumCache + folders[i].getFoldersize();
        }
        std::cout << folders[i].getPath() << " | " << readable_fs(folders[i].getFoldersize()) << " (" << folders[i].getFoldersize() << ")" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Cache: " + readable_fs(sumCache) << std::endl;
    std::cout << "Logs: " + readable_fs(sumLogs) << std::endl;
    std::cout << "Total: " + readable_fs(sumCache + sumLogs) + " can be deleted" << std::endl;
}

void clean(std::vector<PathFolder> folders, bool cache = true, bool logs = true) {
    unsigned int sum = 0;
    for (int i = 0; i < folders.size(); i++) {
        if ((folders[i].isLog() && !logs) || (!folders[i].isLog() && !cache)) {
            continue;
        }

        unsigned int size = folders[i].getFoldersize();
        if (size != 0) {
            
            try{
                folders[i].deleteContents();
            }
            catch (const std::exception& e)
            {
                size = size - folders[i].getFoldersize();
                std::cout << "Some files are in use : ";
            }
            sum = sum + size;
            std::cout << folders[i].getPath() << " Deleted " << readable_fs(size) << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Deleted " << readable_fs(sum) << std::endl;
}

int main()
{
    std::vector<PathFolder> folders = readFolders();
    char input = menu();

    switch (input)
    {
    case 'S':
        scanOnly(folders);
        break;
    case 'E':
        clean(folders);
        break;
    case 'C':
        clean(folders, true, false);
        break;
    case 'L':
        clean(folders, false, true);
        break;
    default:
        scanOnly(folders);
        break;
    }
    
    system("pause");
}