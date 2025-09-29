
#include "Weapon.h"

// NOTE: Remove
#include <iostream>

Weapon::Weapon(sf::Texture& texture, Type type, float proj_speed, float proj_lifetime)
	: GameObject(texture), texture(texture), type(type), projectile_speed(proj_speed), projectile_lifetime(proj_lifetime)
{
	getSprite().setTextureRect({ 0, 16 * type, 16, 16 });
}

Weapon::~Weapon()
{
	for (Projectile* projectile : projectiles)
	{
		delete projectile;
	}
}


void Weapon::update(float dt)
{
	std::cout << projectiles.size() << std::endl;

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i] != nullptr &&
			projectiles[i]->is_loaded)
		{
			projectiles[i]->update(dt);
		}
		else
		{
			// Delete then remove unloaded projectile from vector list
			delete projectiles[i];
			projectiles.erase(std::next(projectiles.begin(), i));
			i--;
		}
	}
}

Projectile* Weapon::shoot(sf::Vector2f position, float angle)
{
	Projectile* projectile = nullptr;

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

	projectile = new Projectile(texture, projectile_lifetime);
	// TODO: Change to originate from centre of player and have smaller hitbox/collider size
	projectile->setCollider({ position.x, position.y, 16, 16 });
	projectile->setVelocity(velocity);
	projectile->getSprite().setTextureRect({ 16, 16 * type, 16, 16 });
	projectile->getSprite().setRotation(angle);

	projectiles.push_back(projectile);

	return projectile;
}


std::vector<Projectile*>& Weapon::getProjectiles()
{
	return projectiles;
}