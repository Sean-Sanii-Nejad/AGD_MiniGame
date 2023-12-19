#pragma once
#include "../utils/Vector2.h"
#include "../graphics/Window.h"
#include "TextureType.h"

enum class TileType {
	CORRIDOR,
	WALL
};

class Tile
{

private:

	TileType type;
	sf::Vector2i position; // Position in the grid (not in screen pixels, for that sprite.getPosition())
	sf::Sprite sprite;

	std::shared_ptr<TextureType> texture;

public:
	void place(int x, int y, float sc);

	Tile(TileType tt, std::shared_ptr<TextureType> textureType) : position(0, 0), type(tt) 
	{
		texture = textureType;
	}

	void loadDefaultTexture();
	void loadTile(int x, int yy, float sc, const std::string& textureFilename = "");

	//void setPosition(int x, int y);
	inline int x() const { return position.x; }
	inline int y() const { return position.y; }
	inline const sf::Vector2f& getScale() const { return sprite.getScale(); }
	inline TileType getType() const { return type; }
	inline float getSpriteXpos() const { return sprite.getPosition().x; }
	inline float getSpriteYpos() const { return sprite.getPosition().y; }
	void draw(Window* window);
};
