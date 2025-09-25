#ifndef _NOTTHEPRISONER_END_H_
#define _NOTTHEPRISONER_END_H_

#include<iostream>
#include <SFML/Graphics.hpp>

class End
{
public:
	End();
	~End();
	void endInit(sf::RenderWindow& window);
	void endRender(sf::RenderWindow& window);

	sf::Font font;
	sf::Text end_text;
};

#endif // _NOTTHEPRISONER_END_HPP_