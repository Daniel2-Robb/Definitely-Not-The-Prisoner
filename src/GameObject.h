#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject
{
public:
	GameObject();
	~GameObject();
	bool initialiseSprite(sf::Texture& texture, std::string filename);
	sf::Sprite* getSprite();
	void movement(float dt);

private:
	sf::Sprite* sprite = nullptr;


};


#endif // PLATFORMER_GAMEOBJECT_H