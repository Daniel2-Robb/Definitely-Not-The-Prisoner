
#ifndef _NOTTHEPRISONER_GAME_H_
#define _NOTTHEPRISONER_GAME_H_

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "Environment/Level.h"
#include "Flavour/Camera.h"
#include "Flavour/Cutscene.h"
#include "Flavour/Menu.h"

class Game
{
private:
	// Rendering/Graphics
	sf::RenderWindow& window;
	Camera camera;

	sf::Texture level_tileset;
	sf::Texture character_spritesheet;
	sf::Texture weapon_spritesheet;

	sf::Font font_default;

	// Game data
	Level* level = nullptr;
	Cutscene* cutscene = nullptr;

	Settings settings;
	Menu* menu = nullptr;

	// Gamestate logic
	enum GameState
	{
		MAINMENU,
		CUTSCENE,
		GAMEPLAY,
		PAUSE,
		END
	} state = MAINMENU;
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