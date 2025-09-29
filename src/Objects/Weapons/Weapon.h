
#ifndef _NOTAPRISONER_WEAPON_H_
#define _NOTAPRISONER_WEAPON_H_

#include <vector>

#include "../GameObject.h"
#include "Projectile.h"

class Weapon : public GameObject
{
private:
	sf::Texture& texture;

	std::vector<Projectile*> projectiles;
	float projectile_speed;
	float projectile_lifetime;

public:
	enum Type
	{
		FISTS,
		PISTOL,
		SHOTGUN
	} const type;

	Weapon(sf::Texture& texture, Type type, float proj_speed, float proj_lifetime);
	~Weapon();

	void update(float dt);
	Projectile* shoot(sf::Vector2f position, float angle);

	std::vector<Projectile*>& getProjectiles();
};

#endif //_NOTAPRISONER_WEAPON_H_