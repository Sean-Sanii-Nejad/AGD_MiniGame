#include "../../include/core/Tile.h"
#include <sstream>
#include <iostream>

void Tile::loadTile(int x, int y, float sc, const std::string& textureFilename)
{
	//load texture (default or by string).
	if (textureFilename.size() > 0)
	{
		if (!texture->texture.loadFromFile(textureFilename))
		{
			std::stringstream sss;
			sss << "Texture file not found: " << textureFilename;
			throw std::exception(sss.str().c_str());
		}
	}
	else {
		loadDefaultTexture();
	}

	//Place tile on the screen.
	place(x, y, sc);
}


void Tile::place(int x, int y, float sc)
{
	//Position in grid:
	position.x = x;
	position.y = y;

	//scale for texture:
	sprite.setScale(sc, sc);

	//Position on screen:
	sf::Vector2u textSize = texture->texture.getSize();
	float pixels_x = static_cast<float>(x * (textSize.x * sc));
	float pixels_y = static_cast<float>(y * (textSize.y * sc));

	sprite.setPosition(pixels_x, pixels_y);
}


void Tile::loadDefaultTexture()
{
	sprite.setTexture(texture->texture);
}


void Tile::draw(Window* window)
{
	window->draw(sprite);
}
