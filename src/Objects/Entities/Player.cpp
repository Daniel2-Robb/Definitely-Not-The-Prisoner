
#include "Player.h"

// NOTE: Remove before commit
#include <iostream>

Player::Player(sf::Texture& texture/*, sf::Texture& weapon_tileset*/) 
	: Entity(texture)
{
	speed = 100.f;
}

Player::~Player()
{
	delete weapon;
}


void Player::update(float dt)
{
	collider.left += velocity.x * dt;
	collider.top += velocity.y * dt;

	weapon->update(dt);
}

void Player::playerInput(Player::Input input)
{
	switch (input)
	{
	/*case Input::IDLE:
		velocity.x = 0;
		velocity.y = 0;
		break;*/

	case Player::Input::START_MOVE_LEFT:
		velocity.x -= speed;
		break;

	case Input::STOP_MOVE_LEFT:
		velocity.x += speed;
		break;

	case Input::START_MOVE_RIGHT:
		velocity.x += speed;
		break;

	case Input::STOP_MOVE_RIGHT:
		velocity.x -= speed;
		break;

	case Input::START_MOVE_UP:
		velocity.y -= speed;
		break;

	case Input::STOP_MOVE_UP:
		velocity.y += speed;
		break;

	case Input::START_MOVE_DOWN:
		velocity.y += speed;
		break;

	case Input::STOP_MOVE_DOWN:
		velocity.y -= speed;
		break;

	case Input::ATTACK:
		weapon->shoot(collider.getPosition(), rotation);
		break;
	}
}