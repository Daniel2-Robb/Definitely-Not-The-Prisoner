
#include "Projectile.h"

Projectile::Projectile(sf::Texture& texture, float lifetime)
	: Entity(texture), lifetime(lifetime)
{
	getSprite();
}


void Projectile::update(float dt)
{
	collider.left += velocity.x * dt;
	collider.top += velocity.y * dt;

	if (timer.getElapsedTime().asMilliseconds() >= lifetime)
	{
		is_loaded = false;
	}
}