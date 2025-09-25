
#include "Game.h"

Game::Game(sf::RenderWindow& window) 
	: window(window), camera(sf::Vector2f(window.getSize().x, window.getSize().y))
{

}

Game::~Game()
{
	delete level;
	delete menu;
	delete cutscene;
}


bool Game::init()
{
	bool success = true;

	// NOTE: Remove after testing
	state = END;

	if (!font.loadFromFile("../content/Fonts/OpenSans-Bold.ttf")) // Replace with a valid font path
	{
		std::cout << "Failed to load font" << std::endl;
		success = false;
	}

	timerText.setFont(font);
	timerText.setCharacterSize(20);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(10.f, 10.f); // Top-left of screen

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
	menu = new Menu();
	end  = new End();
	cutscene->cutsceneInit();
	menu->menuInit(window);
	end->endInit(window);

	camera.setCentre(level->getPlayer().getCollider().getPosition());

	return success;
}

void Game::update(float dt)
{
	switch (state)
	{
	case MENU:
		break;
	case CUTSCENE:
		break;
	case GAMEPLAY:
		level->update(dt);
		level->getPlayer().getSprite().setRotation(90);

		/*if all enemies dead
		* {
		*	state = END;
		* }*/

		// Temporary timer for testing
		elapsedTime += dt;
		int minutes = static_cast<int>(elapsedTime) / 60;
		int seconds = static_cast<int>(elapsedTime) % 60;
		char buffer[16];
		std::sprintf(buffer, "%02d:%02d", minutes, seconds);
		timerText.setString(buffer);

		camera.update(level->getPlayer().getCollider().getPosition(), dt);

		// Calculate parameter values for player aiming
		sf::Vector2i mouse_position = sf::Mouse::getPosition() - window.getPosition();
		sf::Vector2f relative_position(window.getSize().x / 2, window.getSize().y / 2);
		relative_position += level->getPlayer().getCollider().getPosition() - camera.getView().getCenter();
		level->getPlayer().aiming(mouse_position, relative_position);
		break;

	}
}

void Game::render()
{
	switch (state)
	{
	case MENU:
		
		menu->menuRender(window);

		break;

	case CUTSCENE:
		//cutscene->cutscenePlay(window); // TODO: FIX THIS!!!
		state = GAMEPLAY;
		break;

	case GAMEPLAY:
		level->render(window);
		window.setView(camera.getView());
		break;

	case END:
		end->endRender(window);
		break;

	}

	window.draw(timerText);
	
}


void Game::keyboardInput(const sf::Event& event)
{
	bool keydown = (event.type == sf::Event::KeyPressed);

	// TODO: Player input handling (remember to account for menus+cutscenes!)
	if (event.key.code == sf::Keyboard::Escape)
	{
		window.close();
	}

	switch (state)
	{
		

	case MENU:
		//In-menu inputs
		if (event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
		else
		{
			state = CUTSCENE;
		}

		break;

	case CUTSCENE:
		//In-cutscene inputs
		

		break;

	case GAMEPLAY:
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
	case END:
		//In-end screen inputs
		if (event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
		else
		{
			state = MENU;
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