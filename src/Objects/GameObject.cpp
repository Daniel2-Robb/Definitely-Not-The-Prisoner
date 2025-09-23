#include "GameObject.h"
#include <math.h>

GameObject::GameObject(sf::Texture& texture)
{
    sprite = sf::Sprite();
	sprite.setTexture(texture);
}

GameObject::~GameObject()
{

}


sf::Sprite& GameObject::getSprite()
{
	sprite.setPosition(collider.getPosition());

	return sprite;
}

sf::FloatRect GameObject::getCollider()
{
	return collider;
}

void GameObject::setCollider(sf::FloatRect collider)
{
	this->collider = collider;
}

