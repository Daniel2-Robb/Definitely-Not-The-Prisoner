
#ifndef _NOTTHEPRISONER_GAME_H_
#define _NOTTHEPRISONER_GAME_H_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Environment/Level.h"
#include "Flavour/Camera.h"
#include "Flavour/Cutscene.h"
#include "Flavour/Menu.h"
#include "Flavour/End.h"
#include "Flavour/Pause.h"

class Game
{
private:
	// Rendering/Graphics
	sf::RenderWindow& window;
	Camera camera;

	sf::Texture level_tileset;
	sf::Texture character_tileset;
	sf::Texture weapon_tileset;

	// Game data
	Level* level = nullptr;
	Cutscene* cutscene = nullptr;
	Menu* menu = nullptr;
	End* end = nullptr;
	Pause* pause = nullptr;

	// Gamestate logic
	enum GameState
	{
		MENU,
		CUTSCENE,
		GAMEPLAY,
		PAUSE,
		END
	} state = MENU;
	sf::Font font;
	sf::Text timer_text;
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