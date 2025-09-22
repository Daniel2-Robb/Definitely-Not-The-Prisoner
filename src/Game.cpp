
#include "Game.hpp"

Game::Game(sf::RenderWindow& window) : window(window)
{
	
}


bool Game::init()
{
	bool success = true;

	return success;
}

void Game::update(float dt)
{
	
}

void Game::render()
{

}


void Game::keyboard_input(const sf::Event& event)
{
	bool keydown = (event.type == sf::Event::KeyPressed);

	// TODO: Player input handling (remember to account for menus+cutscenes!)
}

void Game::mouse_input(const sf::Event& event)
{

}