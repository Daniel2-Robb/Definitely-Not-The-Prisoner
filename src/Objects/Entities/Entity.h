
#ifndef _NOTTHEPRISONER_ENTITY_H_
#define _NOTTHEPRISONER_ENTITY_H_

#include "../GameObject.h"
#include <iostream>

class Entity : public GameObject
{
protected:
	sf::Vector2f velocity;
	float speed = 0.f;
	float rotation = 0;

public:
	Entity(sf::Texture& texture);

	virtual void update(float dt); // NOTE: Maybe change this to not virtual? (depending on if it's needed or not)
	void collisonResolve(sf::FloatRect rect);
	void rotationTarget(sf::Vector2f target_pos);
	void rotationTarget(sf::Vector2f target_pos, sf::Vector2f relative_pos);

	sf::Vector2f getVelocity();
	float getRotation();
	sf::Sprite& getSprite() override;
	void setVelocity(sf::Vector2f velocity);
};

#endif // _NOTTHEPRISONER_ENTITY_H_