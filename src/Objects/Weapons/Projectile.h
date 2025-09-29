
#ifndef _NOTTHEPRISONER_PROJECTILE_H_
#define _NOTTHEPRISONER_PROJECTILE_H_

#include "../Entities/Entity.h"

class Projectile : public Entity
{
private:
	sf::Clock timer;
	float lifetime;

public:
	Projectile(sf::Texture& texture, float lifetime);

	void update(float dt) override;
};

#endif // _NOTTHEPRISONER_PROJECTILE_H_