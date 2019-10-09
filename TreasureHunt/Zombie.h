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

	float xPos;
	float yPos;
	float speed;

	Device* _device = NULL;

public:
	Zombie(Player* player, Device* device);
	~Zombie();
	void ZombieMove();
};

