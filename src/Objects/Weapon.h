
#ifndef _NOTAPRISONER_WEAPON_H_
#define _NOTAPRISONER_WEAPON_H_

#include <vector>

#include "Entities/Entity.h"
#include "GameObject.h"

class Weapon : public GameObject
{
private:
	

public:
	const bool is_ranged = false;

	// TODO: Add passing both weapon and bullet texture (one texture?)
	//Weapon(bool is_ranged);
	//~Weapon();

	//void shoot(float angle);
};

#endif //_NOTAPRISONER_WEAPON_H_