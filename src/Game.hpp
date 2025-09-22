
#ifndef _NOTTHEPRISONER_GAME_HPP_
#define _NOTTHEPRISONER_GAME_HPP_

#include <SFML/Graphics.hpp>

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
	sf::Texture player_Texture;

	// Player Input
	void keyboard_input(const sf::Event& event);
	void mouse_input(const sf::Event& event);
};

#endif // _NOTTHEPRISONER_GAME_HPP_