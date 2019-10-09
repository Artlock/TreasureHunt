#pragma once
#include <SFML/Graphics.hpp>

#define Z_SPEED 1
#define Z_INDEX 242
#define Z_SCALE 1
#define Z_ANIMATION_FRAME 2

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

	float xPos = 50;
	float yPos = 50;
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

