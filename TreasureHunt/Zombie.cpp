#include "OPTIONS.h"

#include "Zombie.h"
#include "Device.h"
#include "Player.h"
#include "Animator.h"

#include <iostream>

// Warning, the Zombie is currently a Ghost (Ignores collisions)!

Zombie::Zombie(Player* player, Device* device, std::string path)
	: _player(player), _device(device)
{
	_animator = new Animator(path, Z_ANIMATION_FRAME);
	_isMoving = true;
}

Zombie::~Zombie()
{
	_device = NULL;
	_player = NULL;

	if (_animator != NULL) {
		delete _animator;
	}
	_animator = NULL;
}

void Zombie::ZombieMove()
{
	// Get Player's Position
	float _playerPosX = _player->getPosX();
	float _playerPosY = _player->getPosY();

	// Zombie Behavior
	if (xPos >= (_playerPosX - Z_DISTANCE) && xPos <= (_playerPosX + Z_DISTANCE) && yPos >= (_playerPosY - Z_DISTANCE) && yPos <= (_playerPosY + Z_DISTANCE))
	{
		// Damaging Players (Only if player isnt dead and hasn't won)
		if (!_player->isDead() && !_device->hasWin) {
			_player->TakesDamage(Z_DAMAGES * _device->getDeltaTime());
			//std::cout << "I inflicted damage\n";
		}
	}
	else
	{
		// Zombie is moving
		_playerPos = sf::Vector2f(_playerPosX, _playerPosY);
		zombiePosition = sf::Vector2f(xPos, yPos);

		direction = _playerPos - zombiePosition;
		//std::cout << "Direction.x = " << direction.x << " , Direction.y = " << direction.y << std::endl;

		normalizedDir = direction / sqrt((direction.x * direction.x) + (direction.y * direction.y));

		_isMoving = true;
		_lastWasLeft = direction.x >= 0 ? false : true;

		speed = Z_SPEED * _device->getDeltaTime();

		xPos = xPos + normalizedDir.x * speed;
		yPos = yPos + normalizedDir.y * speed;

		sf::Vector2f currentSpeed = normalizedDir * speed;
	}
}

// Display Zombie Sprite
void Zombie::ZombieDraw()
{
	int toDraw = 0;

	if (_isMoving) {
		_animator->Step(_device->getDeltaTime());
		toDraw = _animator->getCurrentSprite();
		_isMoving = false;
	}
	else {
		_animator->Reset();
		toDraw = Z_INDEX;
	}

	_device->addDrawable(toDraw, xPos, yPos, Z_SCALE, 1, yPos, (_lastWasLeft ? 1 : 0), 0, 0);
}
