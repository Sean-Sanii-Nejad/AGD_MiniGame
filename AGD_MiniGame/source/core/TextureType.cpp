#include "../../include/core/TextureType.h"
#include <sstream>

TextureType::TextureType()
{
}

void TextureType::loadTextures(int number)
{
	switch (number)
	{
	case 0:
		if (!texture.loadFromFile("img/floor.png"))
			throw std::exception("floor.png image not found");
		break;

	case 1:
		if (!texture.loadFromFile("img/wall.png"))
			throw std::exception("floor.png image not found");
		break;

	default:
		if (!texture.loadFromFile("img/mushroom50-50.png"))
			throw std::exception("mushroom50-50.png image not found");
		break;
	}
}