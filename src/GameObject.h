
#ifndef _NOTTHEPRISONER_GAMEOBJECT_HPP_
#define _NOTTHEPRISONER_GAMEOBJECT_HPP_

#include <SFML/Graphics.hpp>

class GameObject
{
private:
	// Rendering/Graphics
	sf::Sprite sprite;

protected:
	// Object data
	sf::FloatRect collider;

public:
	GameObject(sf::Texture& texture);

	sf::Sprite& getSprite();
	sf::FloatRect getCollider();
	void setCollider(sf::FloatRect collider);
};


#endif // _NOTTHEPRISONER_GAMEOBJECT_HPP_