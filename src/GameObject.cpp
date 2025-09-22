#include "GameObject.h"
#include <math.h>

GameObject::GameObject(sf::Texture& texture)
{
    sprite = sf::Sprite();
	sprite.setTexture(texture);
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

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
	if (!texture.loadFromFile(filename))
	{
		std::cout << "Could not load texture";
	}

	sprite->setTexture(texture);

	return true;
}