
#include "Game.h"

Game::Game(sf::RenderWindow& window) : window(window)
{
	
}

Game::~Game()
{

}


bool Game::init()
{
	bool success = true;

	//init characters
  //player
	

	return success;
}

void Game::update(float dt)
{
	
}

void Game::render()
{

}


void Game::keyboardInput(const sf::Event& event)
{
	bool keydown = (event.type == sf::Event::KeyPressed);

	// TODO: Player input handling (remember to account for menus+cutscenes!)
}

void Game::mouseInput(const sf::Event& event)
{

}