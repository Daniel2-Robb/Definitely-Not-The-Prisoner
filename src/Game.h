
#ifndef _NOTTHEPRISONER_GAME_H_
#define _NOTTHEPRISONER_GAME_H_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Environment/Level.h"
#include "Flavour/Camera.h"
#include "Flavour/Cutscene.h"
#include "Flavour/Menu.h"
#include "Flavour/End.h"

class Game
{
private:
	// Rendering/Graphics
	sf::RenderWindow& window;
	Camera camera;

	sf::Texture level_tileset;
	sf::Texture character_tileset;

	// Game data
	Level* level = nullptr;
	Cutscene* cutscene = nullptr;
	Menu* menu = nullptr;
	End* end = nullptr;

	// Gamestate logic
	enum GameState
	{
		MENU,
		CUTSCENE,
		GAMEPLAY,
		END
	} state = MENU;
	sf::Font font;
	sf::Text timerText;
	float elapsedTime = 0.f;

	float remainingTime = 300.f;

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