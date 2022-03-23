#include "Textures.hpp"
#include <iostream>
#include <dirent.h>

bool Textures::load(const char *directory) {
    struct dirent *entry;
    std::string dirString = directory;
    DIR *dir = opendir(directory);

    if (dir == nullptr) {
        return false;
    }
    std::cout << std::endl;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        size_t lastIndex = name.find_first_of('.');
        std::string rawName = name.substr(0, lastIndex);
        if (rawName.length() != 0){
            std::cout << rawName << std::endl;
            if (!textures[rawName].loadFromFile(dirString + name)){
                std::cout << rawName << " failed to load!" << std::endl;
                return false;
            }
        }
    }
    closedir(dir);
    return true;
}
