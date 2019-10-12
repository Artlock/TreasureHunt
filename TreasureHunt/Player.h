#pragma once

#include <SFML/Graphics.hpp>

#define PLAYER_SIZE_W 16
#define PLAYER_SIZE_H 16

#define PLAYER_SPEED 100

#define PLAYER_SCALE 1

#define PLAYER_ANIMATION_FRAMES 2

#define PLAYER_IDLE_SPRITE 275

#define PLAYER_LIFE 100

// Forward declaration, avoids having to import things that may change between compilations
class Device;
class Colliders;
class Animator;

class Player
{
public:
	Player(Device* device, Colliders* colliders, std::string path);
	~Player();

	void move(float x, float y);
	void displayPlayer();
	void TakesDamage(float damage);

	inline int getPosX() { return _x; }
	inline int getPosY() { return _y; }

private:
	Device* _device = NULL;
	Colliders* _colliders = NULL;
	Animator* _animator = NULL;

	bool _isMoving = false;
	bool _lastWasLeft = false;

	float _x = 0;
	float _y = 0;
	float _pLife = 0;
};
