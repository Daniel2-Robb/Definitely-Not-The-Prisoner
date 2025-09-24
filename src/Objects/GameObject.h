
#ifndef _NOTTHEPRISONER_GAMEOBJECT_H_
#define _NOTTHEPRISONER_GAMEOBJECT_H_

#include <SFML/Graphics.hpp>

class GameObject
{
private:
	// Rendering/Graphics
	//sf::Sprite sprite;

protected:
	// Object data
	sf::FloatRect collider;
	sf::Sprite sprite;

public:
	GameObject(sf::Texture& texture);
	~GameObject();

	sf::Sprite& getSprite();
	sf::FloatRect getCollider();
	void setCollider(sf::FloatRect collider);
};


#endif // _NOTTHEPRISONER_GAMEOBJECT_HPP_