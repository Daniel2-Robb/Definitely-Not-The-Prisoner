
#include "Menu.h"

#include <iostream>

Menu::Menu(sf::Font& font, Type type, Settings& settings)
	: font(font), type(type), settings(settings)
{
	// TODO: Initialise sf::Text objects
	title_text.setFont(font);
	title_text.setCharacterSize(32);
	title_text.setFillColor(sf::Color(255, 255, 255));
	title_text.setPosition(40.f, 40.f);

	options_text.setFont(font);
	options_text.setCharacterSize(16);
	options_text.setFillColor(sf::Color(255, 255, 255));
	options_text.setPosition(40.f, 72.f);

	// TODO: Adjust size and position based on menu type
	switch (this->type)
	{
	case Type::MAIN:
		title_text.setString("Not A Prisoner");
		options_desc.push_back("Start Game");
		options_desc.push_back("Settings");
		options_desc.push_back("Exit");
		options_outcome.push_back(OptionType::START);
		options_outcome.push_back(OptionType::MENU_SETTINGS);
		options_outcome.push_back(OptionType::BACK);
		break;

	case Type::PAUSE:
		title_text.setString("Paused");
		options_desc.push_back("Resume");
		options_desc.push_back("Exit to Main Menu");
		options_outcome.push_back(OptionType::START);
		options_outcome.push_back(OptionType::BACK);
		break;

	case Type::SETTINGS:
		// TODO: Add SETTINGS options after settings are fully implemented
		title_text.setString("Settings");
		options_desc.push_back("Back");
		options_outcome.push_back(OptionType::BACK);
		break;
	}
}

Menu::Menu(sf::Font& font, Type type, Menu* parent_menu, Settings& settings)
	: Menu(font, type, settings)
{
	parent = parent_menu;
}


void Menu::render(sf::RenderWindow& window)
{
	if (child != nullptr)
	{
		child->render(window);
		return;
	}

	window.draw(title_text);
	
	options_text.setPosition(40.f, 72.f);
	for (int i = 0; i < options_desc.size(); i++)
	{
		options_text.setString((selection == i ? "> " : "  ") + options_desc[i]);
		options_text.move(sf::Vector2f(0, 16.f));
		window.draw(options_text);
	}
}

bool Menu::select()
{
	if (child != nullptr)
	{
		if (child->select())
		{
			delete child;
			child = nullptr;
		}
		return false;
	}

	std::cout << options_outcome.size() << ":" << selection << std::endl;

	switch (options_outcome[selection])
	{
	case START:
		loaded = false;
		break;

	case MENU_SETTINGS:
		child = new Menu(font, Type::SETTINGS, settings);
		selection = 0;
		break;

	case BACK:
		return true;
		break; // NOTE: Not necessary?
	}

	return false;
}


Menu* Menu::getParent()
{
	if (child != nullptr)
	{
		return child->getParent();
	}
	return parent;
}

void Menu::selectUp()
{
	selection--;
	if (selection < 0)
	{
		selection = options_desc.size() - 1;
	}
}

void Menu::selectDown()
{
	selection++;
	if (selection >= options_desc.size())
	{
		selection = 0;
	}
}

bool Menu::getLoaded()
{
	return loaded;
}