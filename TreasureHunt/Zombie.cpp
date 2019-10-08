#include "Zombie.h"


Zombie::Zombie(Player* player)
	: _player(player)
{
	float _playerPosX = _player->getPosX();
	float _playerPosY = _player->getPosY();

	_playerPos = sf::Vector2f(_playerPosX, _playerPosY);
}


Zombie::~Zombie()
{
	if (_player != NULL) {
		delete _player;
	}
	_player = NULL;
}

void Zombie::ZombieMove()
{
	xPos = zombieSprite.getPosition().x;
	yPos = zombieSprite.getPosition().y;

	zombiePosition = sf::Vector2f(xPos, yPos);
	direction = _playerPos - zombiePosition;
	normalizedDir = direction / sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	speed = 1;

	sf::Vector2f currentSpeed = normalizedDir * speed;

	
}


