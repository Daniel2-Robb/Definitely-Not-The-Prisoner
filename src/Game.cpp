
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

	// NOTE: Remove after testing
	state = GAMEPLAY;

	if (!level_tileset.loadFromFile("../content/LevelTilemap.png"))
	{
		std::cout << "LevelTilemap.png failed to load" << std::endl;
		success = false;
	}
	if (!character_tileset.loadFromFile("../content/ActorSpritesheet.png"))
	{
		std::cout << "ActorSpritesheet.png failed to load" << std::endl;
		success = false;
	}

	// NOTE: Remove after finished testing?
	std::array<std::array<Level::Tile, 100>, 100> level_tiles;
	for (auto& row : level_tiles)
	{
		row.fill(Level::Tile::EMPTY);
	}
	std::array<std::array<Level::Tile, 15>, 15> temp_tiles;
	// TODO: make temp_tiles for temp level for testing etc etc
	

	level = new Level(level_tileset, character_tileset, level_tiles);

	return success;
}

void Game::update(float dt)
{
	level->update(dt);
}

void Game::render()
{
	/*switch (state)
	{
	case MENU:
		
		break;

	case CUTSCENE:

		break;

	case GAMEPLAY:
		
		break;

	}*/

	// TODO: Move to within switch statement?
	level->render(window);
}


void Game::keyboardInput(const sf::Event& event)
{
	bool keydown = (event.type == sf::Event::KeyPressed);

	// TODO: Player input handling (remember to account for menus+cutscenes!)

	switch (state)
	{
		

	case MENU:
		//In-menu inputs

		break;

	case CUTSCENE:
		//In-cutscene inputs

		break;

	case GAMEPLAY:
		if (event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
		//In-game inputs

		switch (event.key.scancode)
		{
		case sf::Keyboard::Scancode::A:
		case sf::Keyboard::Scancode::Left:
			level->getPlayer().playerInput(keydown ? Player::Input::START_MOVE_LEFT : Player::Input::STOP_MOVE_LEFT);
			break;

		case sf::Keyboard::Scancode::D:
		case sf::Keyboard::Scancode::Right:
			level->getPlayer().playerInput(keydown ? Player::Input::START_MOVE_RIGHT : Player::Input::STOP_MOVE_RIGHT);
			break;

		case sf::Keyboard::Scancode::W:
		case sf::Keyboard::Scancode::Up:
			level->getPlayer().playerInput(keydown ? Player::Input::START_MOVE_UP : Player::Input::STOP_MOVE_UP);
			break;

		case sf::Keyboard::Scancode::S:
		case sf::Keyboard::Scancode::Down:
			level->getPlayer().playerInput(keydown ? Player::Input::START_MOVE_DOWN : Player::Input::STOP_MOVE_DOWN);
			break;
		}
		break;
	}
}

void Game::mouseInput(const sf::Event& event)
{
	// TODO: Add player mouse input

	if (event.MouseButtonPressed == sf::Mouse::Left)
	{
		level->getPlayer().playerInput(Player::Input::ATTACK);
	}
}