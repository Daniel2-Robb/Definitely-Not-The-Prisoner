
#ifndef _NOTTHEPRISONER_SETTINGS_H_
#define _NOTTHEPRISONER_SETTINGS_H_

#include <SFML/Graphics.hpp>

class Settings
{
private:
	// TODO: Add toggle options

	// Default and alternate keybinds
	struct Keybinds
	{
		// Movement Keys
		sf::Keyboard::Scancode up = sf::Keyboard::Scan::W;
		sf::Keyboard::Scancode down = sf::Keyboard::Scan::S;
		sf::Keyboard::Scancode left = sf::Keyboard::Scan::A;
		sf::Keyboard::Scancode right = sf::Keyboard::Scan::D;
		// Interact Keys
		sf::Keyboard::Scancode select = sf::Keyboard::Scan::Enter;

	} keybind_main, keybind_alt;

public:
	Settings();

	Keybinds& getKeybindMain();
	Keybinds& getKeybindAlternate();
};

#endif // _NOTTHEPRISONER_SETTINGS_H_