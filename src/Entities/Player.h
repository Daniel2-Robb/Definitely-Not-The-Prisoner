
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
		// TODO: Fill with all possible player actions
	};

	Player(sf::Texture& texture);

	void playerInput(Input input);
};

#endif // _NOTTHEPRISONER_PLAYER_H_