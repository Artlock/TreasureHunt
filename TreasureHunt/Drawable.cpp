#include "Drawable.h"
#include "SpriteSheet.h"

Drawable::Drawable(int sprite, int posX, int posY, int scale, int layer, int flipH, int flipV, int flipD)
	: _sprite(sprite), _posX(posX), _posY(posY), _scale(scale), _layer(layer), _flipH(flipH), _flipV(flipV), _flipD(flipD)
{

}

Drawable::~Drawable()
{

}

void Drawable::Draw(SpriteSheet* spriteSheet)
{
	spriteSheet->DrawSprite(_sprite, _posX, _posY, _scale, _flipH, _flipV, _flipD);
}

// Used for better layer comparisons

int Drawable::getPosBottomY() {
	 return _posY + SC_TILE_SIZE_XY * _scale;
}
int Drawable::getPosBottomX() {
	 return _posX + SC_TILE_SIZE_XY * _scale;
}
