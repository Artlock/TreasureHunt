#pragma once

#include <SFML/Graphics.hpp>

#define PLAYER_SIZE_W 16
#define PLAYER_SIZE_Y 16

#define PLAYER_SPEED 100

#define PLAYER_SCALE 1

#define PLAYER_ANIMATION_FRAMES 2

#define PLAYER_IDLE_SPRITE 307

// Forward declaration, avoids having to import things that may change between compilations
class Device;
class Animator;

class Player
{
public:
	Player(Device* device, std::string path);
	~Player();

	void move(float x, float y);
	void displayPlayer();

	inline int getPosX() { return _x; }
	inline int getPosY() { return _y; }

private:
	Device* _device = NULL;
	Animator* _animator = NULL;

	bool _isMoving = false;
	bool _lastWasLeft = false;

	float _x = 0;
	float _y = 0;
};
