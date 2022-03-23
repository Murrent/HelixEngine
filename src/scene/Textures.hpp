#pragma once


#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class Textures {
public:
    std::unordered_map<std::string, sf::Texture> textures;

    bool load(const char *directory);
};

