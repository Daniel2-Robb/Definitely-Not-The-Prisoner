
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

	// NOTE: Remove after finished testing
	std::array<std::array<Level::Tile, 100>, 100> testtiles;
	for (auto& row : testtiles)
	{
		row.fill(Level::Tile::Empty);
	}
	testtiles[2][2] = Level::Wall;
	testtiles[5][3] = Level::Wall;

	level = new Level(level_tileset, character_tileset, testtiles);

	return success;
}

void Game::update(float dt)
{
	// level->update(dt);
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
		//In-game inputs
		Player * player = &level->getPlayer();

		if (event.key.scancode == sf::Keyboard::Scancode::A or event.key.scancode == sf::Keyboard::Left)
		{
			player->playerInput(keydown ? Player::Input::START_MOVE_LEFT : Player::Input::STOP_MOVE_LEFT);
			std::cout << "TEST!" << std::endl;
		}
		else if (event.key.scancode == sf::Keyboard::D or event.key.scancode == sf::Keyboard::Right)
		{
			player->playerInput(keydown ? Player::Input::START_MOVE_RIGHT : Player::Input::STOP_MOVE_RIGHT);
		}
		else if (event.key.scancode == sf::Keyboard::W or event.key.scancode == sf::Keyboard::Up)
		{
			player->playerInput(keydown ? Player::Input::START_MOVE_UP : Player::Input::STOP_MOVE_UP);
		}
		else if (event.key.scancode == sf::Keyboard::S or event.key.scancode == sf::Keyboard::Down)
		{
			player->playerInput(keydown ? Player::Input::START_MOVE_DOWN : Player::Input::STOP_MOVE_DOWN);
		}
		break;
	}
}

void Game::mouseInput(const sf::Event& event)
{
	Player* player = &level->getPlayer();

	// TODO: Add player mouse input

	if (event.MouseButtonPressed == sf::Mouse::Left)
	{
		player->playerInput(Player::Input::SHOOT);
	}
}