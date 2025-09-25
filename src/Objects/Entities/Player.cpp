
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

void Player::aiming()
{
	float mouseX = sf::Mouse::getPosition().x;
	float mouseY = sf::Mouse::getPosition().y;
	vec_x = mouseX - (collider.getPosition().x + (0.5 * collider.getSize().x));
	vec_y = mouseY - (collider.getPosition().y + (0.5 * collider.getSize().y));

	std::cout << mouseX << ":" << mouseY << std::endl;

	rotation_angle = atan(vec_x / vec_y);

	sprite.setOrigin(0 + (0.5 * sprite.getGlobalBounds().width), 0 + (0.5 * sprite.getGlobalBounds().height));
	
	if (vec_x >= 0 && vec_y >= 0)
	{
		rotation_angle += 3.14159 * 0.5;
	}
	if (vec_x >= 0 && vec_y < 0)
	{
		rotation_angle += 3.14159;
	}
	if (vec_x < 0 && vec_y < 0)
	{
		rotation_angle += 3.14159 * 1.5;
	}

	sprite.setRotation(rotation_angle);

	sprite.setOrigin(0, 0);
}