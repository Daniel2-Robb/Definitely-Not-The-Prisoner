
#ifndef _NOTAPRISONER_WEAPON_H_
#define _NOTAPRISONER_WEAPON_H_

#include <vector>

#include "Entities/Entity.h"
#include "GameObject.h"

class Weapon : public GameObject
{
private:
	sf::Texture& texture;

	std::vector<Entity*> projectiles;
	float projectile_speed;
	float projectile_lifetime;
	sf::Clock timer;

public:
	enum WeaponType
	{
		FISTS,
		PISTOL,
		SHOTGUN
	} const type;

	Weapon(sf::Texture& texture, WeaponType type, float proj_speed, float proj_lifetime);
	~Weapon();

	void update(float dt);
	Entity* shoot(sf::Vector2f position, float angle);

	std::vector<Entity*>& getProjectiles();
};

#endif //_NOTAPRISONER_WEAPON_H_