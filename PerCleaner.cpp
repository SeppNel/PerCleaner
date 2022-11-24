#include <iostream>
#include <yaml-cpp/yaml.h>
#include "PathFolder.h"
#include <vector>

#define cout std::cout 

std::vector<PathFolder> readFolders() {
    YAML::Node file = YAML::LoadFile("folders.yaml");
    std::vector<PathFolder> folders;

    for (int i = 0; i < file["Absolute"]["General"].size(); i++)
    {
        std::string path = file["Absolute"]["General"][i].as<std::string>();
        folders.push_back(PathFolder(path));
    }

    for (int i = 0; i < file["Absolute"]["Logs"].size(); i++)
    {
        std::string path = file["Absolute"]["Logs"][i].as<std::string>();
        folders.push_back(PathFolder(path, true));
    }

    std::string user = PathFolder::getUserFolderPath();

    for (int i = 0; i < file["User"]["General"].size(); i++)
    {
        std::string path = file["User"]["General"][i].as<std::string>();
        folders.push_back(PathFolder(user + path));
    }

    for (int i = 0; i < file["User"]["Logs"].size(); i++)
    {
        std::string path = file["User"]["Logs"][i].as<std::string>();
        folders.push_back(PathFolder(user + path, true));
    }

    return folders;
}


int main()
{
    std::vector<PathFolder> folders = readFolders();
    for (int i = 0; i < folders.size(); i++) {
        cout << folders[i].getPath() << " | " << folders[i].isLog() << std::endl;
    }
    
}