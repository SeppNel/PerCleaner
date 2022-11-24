#include <iostream>
#include <yaml-cpp/yaml.h>
#include "Folder.h"
#include <vector>

#define cout std::cout 

std::vector<Folder> readFolders() {
    YAML::Node file = YAML::LoadFile("folders.yaml");
    std::vector<Folder> folders;

    for (int i = 0; i < file["Absolute"]["General"].size(); i++)
    {
        std::string path = file["Absolute"]["General"][i].as<std::string>();
        folders.push_back(Folder(path));
    }

    for (int i = 0; i < file["Absolute"]["Logs"].size(); i++)
    {
        std::string path = file["Absolute"]["Logs"][i].as<std::string>();
        folders.push_back(Folder(path, true, false));
    }

    for (int i = 0; i < file["User"]["General"].size(); i++)
    {
        std::string path = file["User"]["General"][i].as<std::string>();
        folders.push_back(Folder(path, false, true));
    }

    for (int i = 0; i < file["User"]["Logs"].size(); i++)
    {
        std::string path = file["User"]["Logs"][i].as<std::string>();
        folders.push_back(Folder(path, true, true));
    }

    return folders;
}


int main()
{
    std::vector<Folder> folders = readFolders();
    cout << folders[0].getPath() << std::endl << folders[0].isLog();
}