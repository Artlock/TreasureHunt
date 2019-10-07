#pragma once

#include <string>

class Device;
class SpriteSheet;

class Drawable
{
private:
	int _sprite = 0;

	int _posX = 0;
	int _posY = 0;

	int _flipH = 0;
	int _flipV = 0;
	int _flipD = 0;

	int _scale = 0;

	int _layer = 0;

public:
	Drawable(int sprite, int posX, int posY, int scale, int layer, int flipH, int flipV, int flipD);
	~Drawable();

	void Draw(SpriteSheet* spriteSheet);

	// Used for better layer comparisons
	int getPosBottomY();
	int getPosBottomX();

	// Getters
	inline int getSprite() { return _sprite; }

	inline int getPosX() {
		return _posX;
	}

	inline int getPosY() {
		return _posY;
	}

	inline int getFlipH() { return _flipH; }
	inline int getFlipV() { return _flipV; }
	inline int getFlipD() { return _flipD; }

	inline int getScale() { return _scale; }

	inline int getLayer() { return _layer; }
};