
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
	state = CUTSCENE;

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
	// Making temp_tiles for temp level for testing etc etc
	for (auto& row : temp_tiles)
	{
		row.fill(Level::Tile::FLOOR_DEFAULT);
	}
	for (int i = 0; i < 15; i++)
	{
		temp_tiles[0][i] = Level::Tile::WALL;
		temp_tiles[14][i] = Level::Tile::WALL;
		temp_tiles[i][0] = Level::Tile::WALL;
		temp_tiles[i][14] = Level::Tile::WALL;
	}
	temp_tiles[5] = { Level::Tile::WALL, Level::Tile::WALL, Level::Tile::WALL, Level::Tile::WALL, Level::Tile::WALL, Level::Tile::WALL, Level::Tile::WALL, Level::Tile::WALL, Level::Tile::WALL, Level::Tile::WALL, Level::Tile::EMPTY, Level::Tile::EMPTY, Level::Tile::EMPTY, Level::Tile::EMPTY, Level::Tile::WALL };
	temp_tiles[2][2] = Level::Tile::PLAYER_SPAWN;
	temp_tiles[7][2] = Level::Tile::PLAYER_CHECKPOINT;
	temp_tiles[10][10] = Level::Tile::ENEMY_SPAWN;
	temp_tiles[3][12] = Level::Tile::ENEMY_SPAWN;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			level_tiles[i][j] = temp_tiles[i][j];
		}
	}

	level = new Level(level_tileset, character_tileset, level_tiles);
	cutscene = new Cutscene();
	cutscene->setup();

	return success;
}

void Game::update(float dt)
{
	switch (state)
	{
	case MENU:
		break;
	case CUTSCENE:
		cutscene->cutscenePlay(window);
		state = GAMEPLAY;
		break;
	case GAMEPLAY:
		level->update(dt);

		sf::Vector2i mouse_position = sf::Mouse::getPosition();
		mouse_position -= window.getPosition();
		level->getPlayer().aiming(mouse_position);
		break;

	}
}

void Game::render()
{
	switch (state)
	{
	case MENU:
		
		break;

	case CUTSCENE:
		
		break;

	case GAMEPLAY:
		level->render(window);
		break;

	}

	// TODO: Move to within switch statement?
	//level->render(window);
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