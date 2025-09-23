
#ifndef _NOTTHEPRISONER_GAME_H_
#define _NOTTHEPRISONER_GAME_H_

#include <SFML/Graphics.hpp>
#include "Environment/Level.h"

class Game
{
private:
	// Rendering/Graphics
	sf::RenderWindow& window;

	enum GameState
	{
		MENU,
		CUTSCENE,
		GAMEPLAY
	};
	enum GameState state = MENU;

	// Game data
	Level* level = nullptr;

public:
	Game(sf::RenderWindow& window);
	~Game();

	bool init();
	void update(float dt);
	void render();

	
	// Player Input
	void keyboardInput(const sf::Event& event);
	void mouseInput(const sf::Event& event);
};

#endif // _NOTTHEPRISONER_GAME_HPP_