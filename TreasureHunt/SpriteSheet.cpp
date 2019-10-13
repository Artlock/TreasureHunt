#include "OPTIONS.h"

#include "SpriteSheet.h"
#include "Device.h"

SpriteSheet::SpriteSheet(Device* device, std::string texturePath)
	: _device(device)
{
	_image = new sf::Image();
	_image->loadFromFile(texturePath);
	_image->createMaskFromColor(sf::Color::White);

	_texture = new sf::Texture();
	_texture->loadFromImage(*_image);

	_sprite = new sf::Sprite();
	_sprite->setTexture(*_texture);
}

SpriteSheet::~SpriteSheet() // Destructor because ~
{
	_device = NULL;

	delete _rect;
	_rect = NULL;

	delete _texture;
	_texture = NULL;

	delete _sprite;
	_sprite = NULL;
}

// Which sprite from source, and where on destination
void SpriteSheet::DrawSprite(int spriteIndex, int x, int y, int scale, bool flipH, bool flipV, bool flipDiag)
{
	spriteIndex--; // Tiled starts at 1, we start at 0

	if (spriteIndex < 0) return; // 0 from tiled means nothing, it becomes -1 after substraction

	// We will be using center origin instead of top left so we offset the positions by as much as the origins (/ 2)
	// We take into account scale once again (* scale)
	x += SC_TILE_SIZE_XY * scale / 2;
	y += SC_TILE_SIZE_XY * scale / 2;

	// Textures in the image are 16 pixels high / large, there is 1 pixel between each image

	int gridX = spriteIndex % SC_TILE_NB_XY;
	int gridY = (int)floorf((float)spriteIndex / SC_TILE_NB_XY); // Rounds down

	_rect->left = (SC_TILE_SIZE_XY + SC_TILE_GAP_XY) * gridX;
	_rect->top = (SC_TILE_SIZE_XY + SC_TILE_GAP_XY) * gridY;
	_rect->width = SC_TILE_SIZE_XY;
	_rect->height = SC_TILE_SIZE_XY;

	_sprite->setTextureRect(*_rect); // Set location and size in origin sprite
	_sprite->setPosition(x, y); // Set position to draw in destination window

	// Rotation	

	_sprite->setOrigin(SC_TILE_SIZE_XY / 2, SC_TILE_SIZE_XY / 2); // Set origin to center of sprite

	_sprite->setRotation(0); // Reset rotation
	_sprite->setScale(1, 1); // Reset scale

	int angle = 0;
	int scaleX = 1;
	int scaleY = 1;

	if (flipDiag)
	{
		// Overrides
		if (flipH) // Diagonal flip
			angle = 90;
		if (flipV) // Anti diagonal flip
			angle = -90;

		_sprite->setRotation(angle); // Make the object rotate around the origin
	}
	else
	{
		// Can add up
		if (flipH)
			scaleX = -1;
		if (flipV)
			scaleY = -1;

		_sprite->setScale(scaleX, scaleY); // Make the object flip around the origin
	}

	_sprite->setScale(scaleX * scale, scaleY * scale); // Change scale

	// Drawing

	_device->getWindow()->draw(*_sprite); // Draw to window	
}
