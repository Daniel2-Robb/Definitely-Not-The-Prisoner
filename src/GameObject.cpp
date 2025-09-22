#include "GameObject.h"
#include <math.h>

GameObject::GameObject(sf::Texture& texture)
{
    sprite = sf::Sprite();
	sprite.setTexture(texture);
}


sf::Sprite& GameObject::get_sprite()
{
	sprite.setPosition(collider.getPosition());

	return sprite;
}

sf::FloatRect GameObject::get_collider()
{
	return collider;
}

void GameObject::set_collider(sf::FloatRect collider)
{
	this->collider = collider;
}