
#include "Player.h"

Player::Player(sf::Texture& texture) : Entity(texture)
{
	
}


void Player::playerInput(Player::Input input)
{
	// TODO: Modify velocity and held item from type of input

	switch (player_state)
	{
	/*case Input::IDLE:
		velocity.x = 0;
		velocity.y = 0;
		break;*/

	case Input::START_MOVE_LEFT:
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