#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

#define Z_SPEED 1


class Zombie
{
private:
	sf::Vector2f _playerPos = sf::Vector2f(0, 0);
	Player* _player = NULL;

	sf::Sprite zombieSprite;
	sf::Vector2f zombiePosition;
	sf::Vector2f direction;
	sf::Vector2f normalizedDir;

	int xPos;
	int yPos;
	float speed;

public:
	Zombie(Player* player);
	~Zombie();
	void ZombieMove();
};

