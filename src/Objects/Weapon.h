
#ifndef _NOTAPRISONER_WEAPON_H_
#define _NOTAPRISONER_WEAPON_H_

#include <string>
#include <vector>

#include "Entities/Entity.h"
#include "GameObject.h"

class Weapon : public GameObject
{
private:
	std::vector<Entity*> projectiles;
	float projectile_speed;
	float projectile_lifetime;
	sf::Clock timer;

public:
	const std::string name;

	Weapon(sf::Texture& texture, float proj_speed, float proj_lifetime, std::string name);
	~Weapon();

	void update(float dt);
	Entity* shoot(float angle);

	std::vector<Entity*>& getProjectiles();
};

#endif //_NOTAPRISONER_WEAPON_H_