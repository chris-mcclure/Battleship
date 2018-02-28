#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
private:

	/* Array of textures used */
	std::map<std::string, sf::Texture> textures;

public:

	/* Add a texture from a file */
	void loadTexture(const std::string& name, const std::string &filename);

	/* Translate an id into a reference */
	sf::Texture& getRef(const std::string& texture);

	/* Constructor */
	TextureManager()
	{
	}
};

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	/* Load the texture */
	sf::Texture tex;
	tex.loadFromFile(filename);

	/* Add it to the list of textures */
	this->textures[name] = tex;

	return;
}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
	return this->textures.at(texture);
}
