#ifndef _NOTTHEPRISONER_PAUSE_H_
#define _NOTTHEPRISONER_PAUSE_H_

#include <iostream>
#include <SFML/Graphics.hpp>

class Pause
{
public:
	Pause();
	~Pause();
	void pauseInit(sf::RenderWindow& window);
	void pauseRender(sf::RenderWindow& window);

	sf::Text pause_text;
	sf::Font font;
};

#endif // _NOTTHEPRISONER_PAUSE_HPP_