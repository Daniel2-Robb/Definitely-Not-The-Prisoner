
#include "Entity.h"

Entity::Entity(sf::Texture& texture) : GameObject(texture)
{

}


void Entity::update(float dt)
{
	collider.left += velocity.x * dt;
	collider.top += velocity.y * dt;
}

void Entity::collisonResolve(sf::FloatRect rect)
{
	// TODO: Add collision resolution code
}


sf::Vector2f Entity::getVelocity()
{
	return velocity;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}