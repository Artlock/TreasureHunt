#include "Player.h"
#include "Device.h"
#include "Animator.h"
#include "Colliders.h"

#include <iostream>

// Constructor
Player::Player(Device* device, Colliders* colliders, std::string path) : _device(device), _colliders(colliders)
{
	_animator = new Animator(path, PLAYER_ANIMATION_FRAMES);
	_pLife = PLAYER_LIFE;
}

// Destructor
Player::~Player()
{
	_device = NULL;

	if (_animator != NULL)
		delete _animator;
	_animator = NULL;
}

// Update position in space
void Player::move(float x, float y)
{

	if (x != 0.0f)
		_lastWasLeft = x < 0 ? true : false;

	// Player moved, will be useful to know for the animator at the time of drawing
	_isMoving = true;

	float delta = _device->getDeltaTime();

	// Check collision
	if (_colliders->CompareMap(_x + x * PLAYER_SPEED * delta, _y + y * PLAYER_SPEED * delta)) return;

	// Move player
	_x += x * PLAYER_SPEED * delta;
	_y += y * PLAYER_SPEED * delta;

	// Prevent going outside of bounds (X axis)
	if (_x < 0)
		_x = 0;
	else if (_x + PLAYER_SIZE_W * PLAYER_SCALE >= MAP_WIDTH)
		_x = MAP_WIDTH - PLAYER_SIZE_W * PLAYER_SCALE;

	// Prevent going outside of bounds (Y axis)
	if (_y < 0)
		_y = 0;
	else if (_y + PLAYER_SIZE_H * PLAYER_SCALE >= MAP_HEIGHT)
		_y = MAP_HEIGHT - PLAYER_SIZE_H * PLAYER_SCALE;
}

void Player::displayPlayer()
{
	int spriteToDraw = 0;

	if (_isMoving)
	{
		_animator->Step(_device->getDeltaTime());
		spriteToDraw = _animator->getCurrentSprite();
		_isMoving = false;
	}
	else
	{
		_animator->Reset();
		spriteToDraw = PLAYER_IDLE_SPRITE;
	}

	_device->addDrawable(spriteToDraw, _x, _y, PLAYER_SCALE, 1, _y, (_lastWasLeft ? 1 : 0), 0, 0);
}

void Player::TakesDamage(float damage)
{
	if (_pLife > 0) {
		_pLife -= damage;
	}
	else {
		std::cout << "Game Over!\n";
		_device->quit();
	}
	std::cout << "Player's Life = " << _pLife << std::endl;

	_device->lifeBar->setSize(sf::Vector2u(_pLife * 5, 50));
}

bool Player::isDead()
{
	if (_pLife <= 0)
		return true;
	else
		return false;
}
