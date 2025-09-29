
#include "Player.h"

Player::Player(sf::Texture& texture, sf::Texture& weapon_tileset) 
	: Entity(texture), hands(weapon_tileset, Weapon::WeaponType::FISTS, 20.f, 300.f)
{
	speed = 100.f;
}

Player::~Player()
{
	//delete weapon;
}


void Player::update(float dt)
{
	collider.left += velocity.x * dt;
	collider.top += velocity.y * dt;

	if (weapon == nullptr)
	{
		weapon = &hands;
	}
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
		weapon->shoot(collider.getPosition(), rotation);
		break;
	case Input::DROP:
		if (weapon != nullptr)
		{
			weapon->is_loaded = true;

			sf::FloatRect weaponcollider = weapon->getCollider();
			weaponcollider.left = collider.left + collider.width;
			weaponcollider.top = collider.top + collider.height;
			weapon->setCollider(weaponcollider);

			for (Entity* projectile : weapon->getProjectiles())
			{
				projectile->is_loaded = false;
			}

			weapon = nullptr;
		}
		break;
	}
}