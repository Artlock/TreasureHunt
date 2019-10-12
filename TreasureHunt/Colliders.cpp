#include "Colliders.h"
#include "Coordinate.h"
#include "FileToArray.h"
#include "Coordinate.h"

#include "Map.h"
#include "Player.h"

#include <fstream>
#include <list>
#include <iostream>

Colliders::Colliders(std::string pathCollider) : _pathCollider(pathCollider)
{
	Coord = new Coordinate(-1, -1);

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
		// We do two checks player/collider collider/player
		// If we check just the player (4 corners) against the collider (box), the player can walk over a collider if his corners are between the gaps (Big player small collider)
		// If we check just the collider (4 corners) against the player (box), the collider can be entered by a player if its corners dont touch the player (Big collider small player)

		// Check player against collider (Is any corner of the player inside the collider?)
		for (float xBis = x; xBis <= x + TILE_SIZE * PLAYER_SCALE; xBis += TILE_SIZE * PLAYER_SCALE)
		{
			for (float yBis = y; yBis <= y + TILE_SIZE * PLAYER_SCALE; yBis += TILE_SIZE * PLAYER_SCALE)
			{
				if (it->GetX() + GAP <= xBis && it->GetX() + TILE_SIZE * MAP_TILE_SCALE - GAP >= xBis && it->GetY() + GAP <= yBis && it->GetY() + TILE_SIZE * MAP_TILE_SCALE - GAP >= yBis)
				{
					return true;
				}
			}
		}
		
		// Check collider against player (Is any corner of the collider inside the player?)
		for (float ITxBis = it->GetX() + GAP; ITxBis <= it->GetX() + TILE_SIZE * MAP_TILE_SCALE - GAP; ITxBis += TILE_SIZE * MAP_TILE_SCALE - (GAP * 2))
		{
			for (float ITyBis = it->GetY() + GAP; ITyBis <= it->GetY() + TILE_SIZE * MAP_TILE_SCALE - GAP; ITyBis += TILE_SIZE * MAP_TILE_SCALE - (GAP * 2))
			{
				if (ITxBis <= x + TILE_SIZE * PLAYER_SCALE && ITxBis >= x && ITyBis <= y + TILE_SIZE * PLAYER_SCALE && ITyBis >= y)
				{
					return true;
				}
			}
		}
	}
	return false;
}