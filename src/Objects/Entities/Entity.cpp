
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

void Entity::rotationTarget(sf::Vector2i target_pos, sf::Vector2f relative_pos)
{
    // TODO: Modify to get position relative to player location on screen and not absolute level location

    float vec_x = target_pos.x - (relative_pos.x + (0.5 * collider.getSize().x));
    float vec_y = target_pos.y - (relative_pos.y + (0.5 * collider.getSize().y));

    // Calculate player angle based on player and mouse positions
    float rotation_angle = 0.f;
    if ((vec_x >= 0 && vec_y >= 0) ||
        (vec_x < 0 && vec_y < 0))
    {
        rotation_angle = atan(vec_y / vec_x);
    }
    else
    {
        rotation_angle = atan(abs(vec_x / vec_y));
    }

    // Temporarily alter player sprite's origin point for rotation
    //sprite.setOrigin(0.5 * collider.getPosition().x, 0.5 * collider.getPosition().y);


    // Adjust rotation for each potential corner
    if (vec_x >= 0 && vec_y >= 0)
    {
        rotation_angle += 3.14159 * 0.5;
    }
    else if (vec_x < 0 && vec_y >= 0)
    {
        rotation_angle += 3.14159;
    }
    else if (vec_x < 0 && vec_y < 0)
    {
        rotation_angle += 3.14159 * 1.5;
    }
    // Convert from radians to degrees for setRotation method
    rotation_angle = 360 * (rotation_angle / 6.28318);

    sprite.setRotation(rotation_angle + 180); // +180 is due to character textures facing downwards
    rotation = rotation_angle;

    // Reset player origin point to keep other transformations working
    //sprite.setOrigin(0, 0);
}


sf::Vector2f Entity::getVelocity()
{
	return velocity;
}

float Entity::getRotation()
{
    return rotation;
}

sf::Sprite& Entity::getSprite()
{
    sf::Vector2f temp(collider.getSize().x / 2, collider.getSize().y / 2);
    sprite.setOrigin(temp);
    sprite.setPosition(collider.getPosition() + temp);

    return sprite;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}