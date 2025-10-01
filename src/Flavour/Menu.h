
#ifndef _NOTTHEPRISONER_MENU_H_
#define _NOTTHEPRISONER_MENU_H_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Settings.h"

class Menu
{
private:
	// Rendering
	sf::Font& font;
	sf::Text title_text;
	sf::Text options_text;

	// Data
	enum OptionType
	{
		START,
		MENU_SETTINGS,
		BACK
	};
	std::vector<std::string> options_desc;
	std::vector<OptionType> options_outcome;
	int selection = 0;

	Menu* parent = nullptr;
	Menu* child = nullptr;
	Settings& settings;

	// NOTE: Temp?
	bool loaded = true;

public:
	// Menu types
	enum Type
	{
		MAIN,
		PAUSE,
		SETTINGS
	} const type;

	Menu(sf::Font& font, Type type, Settings& settings);
	Menu(sf::Font& font, Type type, Menu* parent_menu, Settings& settings);

	void render(sf::RenderWindow& window);
	bool select();

	Menu* getParent();
	void selectDown();
	void selectUp();

	bool getLoaded();
};

#endif // _NOTTHEPRISONER_MENU_H_