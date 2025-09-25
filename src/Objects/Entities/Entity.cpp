
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
    sf::Vector2f side(0, 0);

    sf::Vector2f selfcorner = collider.getPosition();
    sf::Vector2f othercorner = rect.getPosition() + rect.getSize();

    // Check for simple solves
    if (velocity == sf::Vector2f(0, 0))
    {
        side.y = -1;
    }
    else if (velocity.x == 0)
    {
        side.y = velocity.y > 0 ? -1 : 1;
    }
    else if (velocity.y == 0)
    {
        side.x = velocity.x > 0 ? -1 : 1;
    }
    else
    {
        side.y = velocity.y > 0 ? -1 : 1;
        side.x = velocity.x > 0 ? -1 : 1;

        // Determine velocity origin corners
        if (velocity.x > 0)
        {
            selfcorner.x += collider.width;
            othercorner.x -= rect.width;
        }
        if (velocity.y > 0)
        {
            selfcorner.y += collider.height;
            othercorner.y -= rect.height;
        }

        // Calculate fraction of velocity between each corner for each axis
        float fractionx = (selfcorner.x - othercorner.x) / velocity.x;
        float fractiony = (selfcorner.y - othercorner.y) / velocity.y;

        // Check which axis is closer accounting for velocity
        // (aka which side would be easiest to get to with the current velocity)
        if (fractiony > fractionx)
        {
            side.y = 0;
        }
        else
        {
            side.x = 0;
        }
    }

    // Correct position of Entity collider and reset correct velocity
    if (side.x == 1)
    {
        collider.left = rect.left + rect.width;
        //velocity.x = 0;
    }
    if (side.x == -1)
    {
        collider.left = rect.left - collider.width;
        //velocity.x = 0;
    }
    if (side.y == 1)
    {
        collider.top = rect.top + rect.height;
        //velocity.y = 0;
    }
    if (side.y == -1)
    {
        collider.top = rect.top - collider.height;
        //velocity.y = 0;
    }
}


sf::Vector2f Entity::getVelocity()
{
	return velocity;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}


sf::Sprite& Entity::getSprite()
{
    sf::Vector2f temp(collider.getSize().x / 2, collider.getSize().y / 2);
    sprite.setOrigin(temp);
    sprite.setPosition(collider.getPosition() + temp);

    return sprite;
}