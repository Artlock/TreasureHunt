#include "Colliders.h"
#include "Coordinate.h"
#include "FileToArray.h"

#include <fstream>
#include <list>
#include <iostream>

Colliders::Colliders(std::string pathCollider) : _pathCollider(pathCollider)
{
	Coord = new Coordinate(-1,-1);

	FileToArray<unsigned long>::ReadFileTo_Array_2D(_pathCollider, MAP_SIZE_H, MAP_SIZE_W, _ColliderData);
}

Colliders::~Colliders() 
{
	
}

void Colliders::MakeList(int tileSize)
{
	unsigned long Index = 0;
	float x = 0.f;
	float y = 0.f;

	for (int i = 0; i < MAP_SIZE_H; i++)
		for (int j = 0; j < MAP_SIZE_W; j++)
		{
			// Get raw sprite index with flags
			Index = _ColliderData[i][j];

			x = j * tileSize * MAP_TILE_SCALE; // Pixels on x, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			y = i * tileSize * MAP_TILE_SCALE; // Pixels on y, taking into account scale (Only works in this context for scale since we're drawing from 0 to END)
			Coord->changeCoordinate(x, y);
			if (Index != 0) 
			{
				listCoord.push_back(*Coord);
			}
		}
}

bool Colliders::CompareMap(float x, float y)
{
	for (std::list<Coordinate>::iterator it = listCoord.begin(); it != listCoord.end(); ++it) 
	{
		for (float xBis = x; xBis <= x + TILE_SIZE; xBis += TILE_SIZE) 
		{
			for (float yBis = y; yBis <= y + TILE_SIZE; yBis += TILE_SIZE)
			{
				if (it->GetX()+3 <= xBis && it->GetX()+TILE_SIZE-3 >= xBis && it->GetY()+3 <= yBis && it->GetY()+TILE_SIZE-3 >= yBis)
				{
					return true;
				}
			}
		}

		for (float ITxBis = it->GetX()+3; ITxBis <= it->GetX() + TILE_SIZE-3; ITxBis += TILE_SIZE-2*3)
		{
			for (float ITyBis = it->GetY()+3; ITyBis <= it->GetY() + TILE_SIZE-3; ITyBis += TILE_SIZE-2*3)
			{
				if (ITxBis <= x + TILE_SIZE && ITxBis >= x && ITyBis <= y+TILE_SIZE && ITyBis >= y)
				{
					return true;
				}
			}
		}
	}
	return false;
}