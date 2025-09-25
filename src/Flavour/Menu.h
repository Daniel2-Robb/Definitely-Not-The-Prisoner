#ifndef _NOTTHEPRISONER_MENU_H_
#define _NOTTHEPRISONER_MENU_H_

#include <iostream>
#include <SFML/Graphics.hpp>

class Menu
{
	public:
	Menu();
	~Menu();
	void menuInit(sf::RenderWindow& window);
	void menuRender(sf::RenderWindow& window);

	sf::Font font;
	sf::Text menu_text;
	sf::Text controls;
	sf::Text start;
};

#endif // _NOTTHEPRISONER_MENU_HPP_