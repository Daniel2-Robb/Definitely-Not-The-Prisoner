
#ifndef _NOTTHEPRISONER_GAME_HPP_
#define _NOTTHEPRISONER_GAME_HPP_

#include <SFML/Graphics.hpp>

class Game
{
private:
	// Rendering/Graphics
	sf::RenderWindow& window;

public:
	Game(sf::RenderWindow& window);

	bool init();
	void update(float dt);
	void render();

	// Player Input
	void keyboard_input(const sf::Event& event);
	void mouse_input(const sf::Event& event);
};

#endif // _NOTTHEPRISONER_GAME_HPP_