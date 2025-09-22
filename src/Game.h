
#ifndef _NOTTHEPRISONER_GAME_HPP_
#define _NOTTHEPRISONER_GAME_HPP_

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Game
{
private:
	// Rendering/Graphics
	sf::RenderWindow& window;

	bool in_menu = false;
	bool in_cutscene = false;

public:
	Game(sf::RenderWindow& window);
	~Game();

	bool init();
	void update(float dt);
	void render();

	GameObject player;
	sf::Texture player_texture;

	GameObject enemies[19];
	sf::Texture enemy_texture;

	// Player Input
	void keyboardInput(const sf::Event& event);
	void mouseInput(const sf::Event& event);
};

#endif // _NOTTHEPRISONER_GAME_HPP_