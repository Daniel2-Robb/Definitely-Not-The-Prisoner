
#ifndef _NOTTHEPRISONER_PLAYER_H_
#define _NOTTHEPRISONER_PLAYER_H_

#include "../Weapon.h"
#include "Entity.h"

class Player : public Entity
{
private:
	// Default weapon
	//Weapon hands;


public:
	// Held weapon
	//Weapon* weapon = nullptr;

	// All types of player input
	enum Input
	{
		IDLE,
		START_MOVE_LEFT,
		STOP_MOVE_LEFT,
		START_MOVE_RIGHT,
		STOP_MOVE_RIGHT,
		START_MOVE_UP,
		STOP_MOVE_UP,
		START_MOVE_DOWN,
		STOP_MOVE_DOWN,
		ATTACK
	};

	Input player_state = IDLE;

	Player(sf::Texture& texture/*, sf::Texture& weapon_tileset*/);
	
	void playerInput(Input input);
};

#endif // _NOTTHEPRISONER_PLAYER_H_