#include "Player.h"
#include "Device.h"
#include "Animator.h"

// Constructor
Player::Player(Device* device, std::string path) : _device(device)
{
	_animator = new Animator(path, PLAYER_ANIMATION_FRAMES);
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

	// Move player
	_x += x * PLAYER_SPEED * _device->getDeltaTime();
	_y += y * PLAYER_SPEED * _device->getDeltaTime();

	// Prevent going outside of bounds (X axis)
	if (_x < 0)
		_x = 0;
	else if (_x + PLAYER_SIZE_W * PLAYER_SCALE >= _device->getWindow()->getSize().x)
		_x = _device->getWindow()->getSize().x - PLAYER_SIZE_W * PLAYER_SCALE;

	// Prevent going outside of bounds (Y axis)
	if (_y < 0)
		_y = 0;
	else if (_y + PLAYER_SIZE_Y * PLAYER_SCALE >= _device->getWindow()->getSize().y)
		_y = _device->getWindow()->getSize().y - PLAYER_SIZE_Y * PLAYER_SCALE;
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

	_device->addDrawable(spriteToDraw, _x, _y, PLAYER_SCALE, 1, 0, (_lastWasLeft ? 1 : 0), 0);
}