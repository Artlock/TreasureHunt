#include "Zombie.h"


Zombie::Zombie(Player* player, Device* device)
	: _player(player), _device(device)
{
	
}


Zombie::~Zombie()
{
	if (_player != NULL) {
		delete _player;
	}
	_player = NULL;

	if (_device != NULL) {
		delete _device;
	}
	_device = NULL;
}

void Zombie::ZombieMove()
{
	float _playerPosX = _player->getPosX();
	float _playerPosY = _player->getPosY();

	_playerPos = sf::Vector2f(_playerPosX, _playerPosY);
	zombiePosition = sf::Vector2f(xPos, yPos);

	direction = _playerPos - zombiePosition;
	normalizedDir = direction / sqrt((direction.x * direction.x) + (direction.y * direction.y));

	speed = Z_SPEED * _device->getDeltaTime();

	xPos = xPos + normalizedDir.x * speed;
	yPos = yPos + normalizedDir.y * speed;

	sf::Vector2f currentSpeed = normalizedDir * speed;

	
}


