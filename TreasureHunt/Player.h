#pragma once

#include <SFML/Graphics.hpp>

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

	float _pLife = 0;

	bool isDead();

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
};
