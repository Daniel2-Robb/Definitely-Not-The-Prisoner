#include "Menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::menuInit(sf::RenderWindow& window)
{
	font.loadFromFile(("../content/Fonts/OpenSans-Bold.ttf"));

	menu_text.setString("Welcome to: Fight 'Em 'Til You Can't"); //working title
	menu_text.setFont(font);
	menu_text.setCharacterSize(25);
	menu_text.setFillColor(sf::Color(0, 0, 0, 255));
	menu_text.setPosition((window.getSize().x / 2) - (menu_text.getGlobalBounds().width / 2), 100);

	controls.setString("Arrow Keys / WASD to move, Click to attack");
	controls.setFont(font);
	controls.setCharacterSize(20);
	controls.setFillColor(sf::Color(0, 0, 0, 255));
	controls.setPosition((window.getSize().x / 2) - (controls.getGlobalBounds().width / 2), 150 + menu_text.getGlobalBounds().height);

	start.setString("Press any key to continue");
	start.setFont(font);
	start.setCharacterSize(20);
	start.setFillColor(sf::Color(0, 0, 0, 255));
	start.setPosition((window.getSize().x / 2) - (start.getGlobalBounds().width / 2), 200 + menu_text.getGlobalBounds().height + controls.getGlobalBounds().height);

}

void Menu::menuRender(sf::RenderWindow& window)
{
	window.draw(menu_text);
	window.draw(controls);
	window.draw(start);

}