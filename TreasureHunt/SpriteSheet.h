#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#define SC_TILE_NB_XY 32

#define SC_TILE_SIZE_XY 16
#define SC_TILE_GAP_XY 1

class Device;

class SpriteSheet
{
private:
	Device* _device = NULL;

	sf::Texture* _texture = NULL;
	sf::Sprite* _sprite = NULL;

	sf::IntRect* _rect = new sf::IntRect(0, 0, 0, 0);

public:
	SpriteSheet(Device* device, std::string texturePath); // Constructor
	~SpriteSheet(); // Destructor because ~

	void DrawSprite(int spriteIndex, int x, int y, int scale, bool flipH = false, bool flipV = false, bool flipDiag = false);
};
