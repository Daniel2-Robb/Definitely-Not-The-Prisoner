
#include "Player.h"

Player::Player(sf::Texture& texture) : Entity(texture)
{
	
}


void Player::playerInput(Player::Input input)
{
	// TODO: Modify velocity and held item from type of input

	switch (player_state)
	{
	/*case IDLE:
		velocity.x = 0;
		velocity.y = 0;*/
	case START_MOVE_LEFT:
		velocity.x -= speed;

	case STOP_MOVE_LEFT:
		velocity.x += speed;

	case START_MOVE_RIGHT:
		velocity.x += speed;

	case STOP_MOVE_RIGHT:
		velocity.x -= speed;

	case START_MOVE_UP:
		velocity.y -= speed;

	case STOP_MOVE_UP:
		velocity.y += speed;

	case START_MOVE_DOWN:
		velocity.y += speed;

	case STOP_MOVE_DOWN:
		velocity.y -= speed;

	case SHOOT:
		playerShoot();
	}
	
}

void playerShoot()
{

}