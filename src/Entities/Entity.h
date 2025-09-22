
#ifndef _NOTTHEPRISONER_ENTITY_H_
#define _NOTTHEPRISONER_ENTITY_H_

#include "../GameObject.h"

class Entity : public GameObject
{
protected:
	sf::Vector2f velocity;

public:
	Entity(sf::Texture& texture);

	virtual void update(float dt); // NOTE: Maybe change this to not virtual? (depending on if it's needed or not)

	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f velocity);
};

#endif // _NOTTHEPRISONER_ENTITY_H_