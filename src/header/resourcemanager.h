#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem> 
#include <map>

class ResourceManager
{
public:
    explicit ResourceManager(const std::string& resourceDir) : resourcePath{ resourceDir }
    {
        if (!std::filesystem::exists(resourcePath))
        {
            resourcePath = ".";
            std::cout << "Couldn't find " + resourceDir + ". Using bin directory instead.\n";
        }
    }

    bool loadImage(const std::string& name, const std::string& fileName)
    {
        sf::Image image;
        std::filesystem::path filePath{ resourcePath / fileName };
        if (image.loadFromFile(filePath.string()))
        {
            images[name] = image;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool loadTexture(const std::string& name, const std::string& fileName)
    {
        sf::Texture texture;
        std::filesystem::path filePath{ resourcePath / fileName };
        if (texture.loadFromFile(filePath.string()))
        {
            textures[name] = texture;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool loadFont(const std::string& name, const std::string& fileName)
    {
        sf::Font font;
        std::filesystem::path filePath{ resourcePath / fileName };
        if (font.loadFromFile(filePath.string()))
        {
            fonts[name] = font;
            return true;
        }
        else
        {
            return false;
        }
    }

    const sf::Image& getImage(const std::string& name) const
    {
        return images.at(name);
    }

    const sf::Texture& getTexture(const std::string& name) const
    {
        return this->textures.at(name);
    }

    const sf::Font& getFont(const std::string& name) const
    {
        return this->fonts.at(name);
    }

private:
    std::filesystem::path resourcePath;
    std::map<std::string, sf::Image> images;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};