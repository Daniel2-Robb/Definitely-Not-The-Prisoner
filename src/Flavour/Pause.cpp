#include "Pause.h"

Pause::Pause()
{

}

Pause::~Pause()
{

}

void Pause::pauseInit(sf::RenderWindow& window)
{
	font.loadFromFile(("../content/Fonts/OpenSans-Bold.ttf"));

	pause_text.setString("Game Paused");
	pause_text.setFont(font);
	pause_text.setCharacterSize(30);
	pause_text.setFillColor(sf::Color(0, 0, 0, 255));
	pause_text.setPosition((window.getSize().x / 2) - (pause_text.getGlobalBounds().width / 2), (window.getSize().y / 2) - (pause_text.getGlobalBounds().height / 2));

}

void Pause::pauseRender(sf::RenderWindow& window)
{
	window.draw(pause_text);
}