
#include "Weapon.h"

Weapon::Weapon(sf::Texture& texture, Type type)
	: GameObject(texture), texture(texture), type(type)
{
	getSprite().setTextureRect({ 0, 16 * type, 16, 16 });

	switch (type)
	{
	case FISTS:
		projectile_speed = 40.f;
		projectile_lifetime = 200.f;
		break;
	case PISTOL:
		projectile_speed = 300.f;
		projectile_lifetime = 3000.f;
		break;
	}
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
	sf::Vector2f offset;

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
	// TODO: Change to originate more from centre of player and have smaller hitbox/collider size
	projectile->setVelocity(velocity);
	projectile->getSprite().setTextureRect({ 16, 16 * type, 16, 16 });
	projectile->getSprite().setRotation(angle);

	// TODO: Modify position to match with player rotation visually
	/*offset = velocity;
	offset.x *= 8 / projectile_speed;
	offset.y *= 8 / projectile_speed;
	
	position.x += 8 + offset.x;
	position.y += 8 + offset.y;*/

	if (type == Type::FISTS)
	{
		projectile->setCollider({ position.x + 5, position.y + 5, 6, 6 });
	}
	else
	{
		projectile->setCollider({ position.x + 6, position.y + 6, 4, 4 });
	}

	projectiles.push_back(projectile);

	return projectile;
}


std::vector<Projectile*>& Weapon::getProjectiles()
{
	return projectiles;
}