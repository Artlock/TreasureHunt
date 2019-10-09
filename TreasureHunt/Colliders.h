#pragma once
#include <string>
#include <list>
#include "Coordinate.h"

#define MAP_TILE_SCALE 1

#define MAP_SIZE_W 48
#define MAP_SIZE_Y 24

class Colliders
{
private:
	std::string _pathCollider = "";
	unsigned long** _ColliderData = NULL;
	std::list<Coordinate> listCoord;
	Coordinate* Coord = NULL;
public:
	Colliders(std::string pathCollider);
	~Colliders();
	void MakeList(int tileSize);
	bool Compare(float x, float y);
};

