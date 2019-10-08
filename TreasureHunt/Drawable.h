#pragma once

#include <string>

class Device;
class SpriteSheet;

class Drawable
{
private:
	int _id = 0; // ID of current sprite
	int _baseID = 0; // ID of sprite we're above. If this isn't equal to -1 then we display our drawable after its base has been displayed

	int _sprite = 0;

	int _posX = 0;
	int _posY = 0;

	int _flipH = 0;
	int _flipV = 0;
	int _flipD = 0;

	int _scale = 0;

	int _layer = 0;

public:
	Drawable(int sprite, int posX, int posY, int scale, int layer, int flipH, int flipV, int flipD, int id, int baseID);
	~Drawable();

	void Draw(SpriteSheet* spriteSheet);

	// Used for better layer comparisons
	int getPosBottomY();
	int getPosBottomX();

	// Getters
	inline int getID() { return _id; }
	inline int getBaseID() { return _baseID; }

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
