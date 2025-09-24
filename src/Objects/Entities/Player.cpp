
#include "Player.h"

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

void Player::aiming(float mouseX, float mouseY)
{
	float vec_x = mouseX - (collider.getPosition().x + 0.5 * collider.getSize().x);
	float vec_y = mouseY - (collider.getPosition().y + 0.5 * collider.getSize().y);
	
	float hypotinuse = sqrt((mouseX * mouseX) + (mouseY * mouseY));

	float rotation_angle = sinf(vec_x / hypotinuse);

	//sprite.rotate(sf::degrees(rotation_angle));
}