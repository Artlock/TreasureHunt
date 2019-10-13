#pragma once

#include <SFML/Graphics.hpp>

class Device;
class Player;
class Animator;

class Zombie
{
private:
	sf::Vector2f _playerPos = sf::Vector2f(0, 0);
	sf::Vector2f zombiePosition;
	sf::Vector2f direction;
	sf::Vector2f normalizedDir;

	bool _isMoving = false;
	bool _lastWasLeft = false;

	float xPos = 150;
	float yPos = 150;
	float speed = 0;

	Player* _player = NULL;
	Device* _device = NULL;
	Animator* _animator = NULL;

public:
	Zombie(Player* player, Device* device, std::string path);
	~Zombie();
	void ZombieMove();
	void ZombieDraw();
};

