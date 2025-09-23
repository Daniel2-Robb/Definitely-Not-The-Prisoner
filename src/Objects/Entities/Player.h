
#ifndef _NOTTHEPRISONER_PLAYER_H_
#define _NOTTHEPRISONER_PLAYER_H_

#include "Entity.h"

class Player : public Entity
{
private:
	// TODO: Add held item/weapon when implemented?


public:
	// All types of player input
	enum Input
	{
		// TODO: Fill with all possible player actions#
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

	Player(sf::Texture& texture);
	
	void playerInput(Input input);
};

#endif // _NOTTHEPRISONER_PLAYER_H_