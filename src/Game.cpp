
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
	player.initialiseSprite(player_texture, "../Data/Images/kenney_pixelplatformer/Characters/character_0000.png");
	player.getSprite()->setPosition(50, 300);

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