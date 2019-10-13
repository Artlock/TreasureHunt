#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <list>

class Coordinate;

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
	bool CompareMap(float x, float y);
};

