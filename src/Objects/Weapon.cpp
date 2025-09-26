
#include "Weapon.h"

Weapon::Weapon(sf::Texture& texture, float proj_speed, float proj_lifetime, std::string name)
	: GameObject(texture), texture(texture), projectile_speed(proj_speed), projectile_lifetime(proj_lifetime), name(name)
{
}

Weapon::~Weapon()
{
	for (Entity* projectile : projectiles)
	{
		delete projectile;
	}
}


void Weapon::update(float dt)
{
	for (Entity* projectile : projectiles)
	{
		if (projectile != nullptr &&
			projectile->is_loaded)
		{
			projectile->update(dt);
			// TODO: Check entity lifetime and delete if over it
		}
		else
		{
			// TODO: Remove null pointer from vector list
		}
	}
}

Entity* Weapon::shoot(sf::Vector2f position, float angle)
{
	Entity* projectile = nullptr;

	sf::Vector2f velocity;

	float radians = (float((int(angle) % 90)) / 360) * 6.28318;
	float opposite = sin(radians) * projectile_speed;
	float adjacent = cos(radians) * projectile_speed;

	if (angle >= 0 && angle < 90)
	{
		velocity = sf::Vector2f(opposite, -adjacent);
	}
	else if (angle >= 90 && angle < 180)
	{
		velocity = sf::Vector2f(adjacent, opposite);
	}
	else if (angle >= 180 && angle < 270)
	{
		velocity = sf::Vector2f(-opposite, adjacent);
	}
	else
	{
		velocity = sf::Vector2f(-adjacent, -opposite);
	}

	projectile = new Entity(texture);
	projectile->setCollider({ position.x, position.y, 16, 16 });
	projectile->setVelocity(velocity);
	projectile->getSprite().setTextureRect({ 0, 0, 16, 16 });

	projectiles.push_back(projectile);

	return projectile;
}


std::vector<Entity*>& Weapon::getProjectiles()
{
	return projectiles;
}