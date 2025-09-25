
#include "Player.h"

// NOTE: Remove before commit
#include <iostream>

Player::Player(sf::Texture& texture) : Entity(texture)
{
	speed = 100.f;
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
		// TODO: Add attack command when weapons added
		break;
	}
}

void Player::aiming(sf::Vector2i mousepos)
{
	// TODO: Modify to get position relative to player location on screen and not absolute level location

	float vec_x = mousepos.x - (collider.getPosition().x + (0.5 * collider.getSize().x));
	float vec_y = mousepos.y - (collider.getPosition().y + (0.5 * collider.getSize().y));

	// Calculate player angle based on player and mouse positions
	float rotation_angle = 0.f;
	if ((vec_x >= 0 && vec_y >= 0) ||
		(vec_x < 0 && vec_y < 0))
	{
		rotation_angle = atan(vec_y / vec_x);
	}
	else
	{
		rotation_angle = atan(abs(vec_x / vec_y));
	}

	// Temporarily alter player sprite's origin point for rotation
	//sprite.setOrigin(0.5 * collider.getPosition().x, 0.5 * collider.getPosition().y);

	
	// Adjust rotation for each potential corner
	if (vec_x >= 0 && vec_y >= 0)
	{
		rotation_angle += 3.14159 * 0.5;
	}
	else if (vec_x < 0 && vec_y >= 0)
	{
		rotation_angle += 3.14159;
	}
	else if (vec_x < 0 && vec_y < 0)
	{
		rotation_angle += 3.14159 * 1.5;
	}
	// Convert from radians to degrees for setRotation method
	rotation_angle = 360 * (rotation_angle / 6.28318);

	sprite.setRotation(rotation_angle + 180);

	// Reset player origin point to keep other transformations working
	//sprite.setOrigin(0, 0);
}