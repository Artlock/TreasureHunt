#include "Drawable.h"
#include "SpriteSheet.h"
#include "Coordinate.h"

Drawable::Drawable(int sprite, int posX, int posY, int scale, int layer, int posDrawAfterY, int flipH, int flipV, int flipD)
	: _sprite(sprite), _posX(posX), _posY(posY), _scale(scale), _layer(layer), _posDrawAfterY(posDrawAfterY), _flipH(flipH), _flipV(flipV), _flipD(flipD)
{

}

Drawable::~Drawable()
{

}

void Drawable::Draw(SpriteSheet* spriteSheet, Coordinate* offSet)
{
	spriteSheet->DrawSprite(_sprite, _posX-offSet->GetX(), _posY - offSet->GetY(), _scale, _flipH, _flipV, _flipD);
}
