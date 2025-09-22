#include "GameObject.h"
#include <math.h>

GameObject::GameObject()
{
    sprite = new sf::Sprite();
}

GameObject::~GameObject()
{
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    }
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

sf::Sprite* GameObject::getSprite()
{
    return sprite;
}

void GameObject::movement(float dt)
{

}