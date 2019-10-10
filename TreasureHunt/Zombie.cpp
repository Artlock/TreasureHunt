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
	if (_player != NULL) {
		delete _player;
	}
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
	/*if (_isMoving) {
		_playerPos = sf::Vector2f(_playerPosX, _playerPosY);
		zombiePosition = sf::Vector2f(xPos, yPos);

		direction = _playerPos - zombiePosition;
		std::cout << "Direction.x = " << direction.x << " , Direction.y = " << direction.y << std::endl;
		normalizedDir = direction / sqrt((direction.x * direction.x) + (direction.y * direction.y));
		std::cout << "normalized Direction X = " << normalizedDir.x << " , Normalized Direction Y = " << normalizedDir.y << std::endl;

		_isMoving = true;

		speed = Z_SPEED * _device->getDeltaTime();

		xPos = xPos + normalizedDir.x * speed;
		yPos = yPos + normalizedDir.y * speed;

		sf::Vector2f currentSpeed = normalizedDir * speed;
	}*/

	// Player take Damage
	if (xPos >= (_playerPosX - 5) && xPos <= (_playerPosX + 5) && yPos >= (_playerPosY - 5) && yPos <= (_playerPosY + 5)) {
		_player->TakesDamage(5 * _device->getDeltaTime());
		std::cout << "I inflict damage\n";
	}

	// Zombie stopping
	if (xPos >= (_playerPosX - 3) && xPos <= (_playerPosX + 3) && yPos >= (_playerPosY - 3) && yPos <= (_playerPosY + 3)) {
		//_isMoving = false;
		std::cout << "I stop moving\n";
	}
	else {
		// _isMoving = true;
		_playerPos = sf::Vector2f(_playerPosX, _playerPosY);
		zombiePosition = sf::Vector2f(xPos, yPos);

		direction = _playerPos - zombiePosition;
		std::cout << "Direction.x = " << direction.x << " , Direction.y = " << direction.y << std::endl;
		normalizedDir = direction / sqrt((direction.x * direction.x) + (direction.y * direction.y));
		std::cout << "normalized Direction X = " << normalizedDir.x << " , Normalized Direction Y = " << normalizedDir.y << std::endl;

		_isMoving = true;

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
		std::cout << toDraw << std::endl;
	}

	_device->addDrawable(toDraw, xPos, yPos, Z_SCALE, 1, false, 0, 0);
}


