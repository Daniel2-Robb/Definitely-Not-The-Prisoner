#ifndef _NOTTHEPRISONER_CUTSCENE_H_
#define _NOTTHEPRISONER_CUTSCENE_H_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>

class Cutscene
{
protected :


public:
	Cutscene();
	~Cutscene();
	void setup();
	void cutscenePlay();

	int player_life = 2;

	sf::Text player_text;
	sf::Text number_2_text;
	sf::Font font;
};

#endif // _NOTTHEPRISONER_CUTSCENE_HPP_