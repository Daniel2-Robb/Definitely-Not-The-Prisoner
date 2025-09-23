
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

	switch (state)
	{
	case MENU:
		//In-menu inputs

	case CUTSCENE:
		//In-cutscene inputs

	case GAMEPLAY:
		//In-game inputs
		Player * player = &level->getPlayer();

		if (event.key.code == sf::Keyboard::A or event.key.code == sf::Keyboard::Left)
		{
			player->playerInput(keydown ? Player::Input::START_MOVE_LEFT : Player::Input::STOP_MOVE_LEFT);
		}
		else if (event.key.code == sf::Keyboard::D or event.key.code == sf::Keyboard::Right)
		{
			player->playerInput(keydown ? Player::Input::START_MOVE_RIGHT : Player::Input::STOP_MOVE_RIGHT);
		}
		else if (event.key.code == sf::Keyboard::W or event.key.code == sf::Keyboard::Up)
		{
			player->playerInput(keydown ? Player::Input::START_MOVE_UP : Player::Input::STOP_MOVE_UP);
		}
		else if (event.key.code == sf::Keyboard::S or event.key.code == sf::Keyboard::Down)
		{
			player->playerInput(keydown ? Player::Input::START_MOVE_DOWN : Player::Input::STOP_MOVE_DOWN);
		}
	}
}

void Game::mouseInput(const sf::Event& event)
{
	Player* player = &level->getPlayer();

	if (event.key.code == sf::Mouse::Left)
	{
		player->playerInput(mouseInput ? Player::Input::SHOOT : Player::Input::IDLE);
	}
}