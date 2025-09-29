
#include "Game.h"

Game::Game(sf::RenderWindow& window) 
	: window(window), camera(window)
{

}

Game::~Game()
{
	delete level;
	delete menu;
	delete cutscene;
	delete end;
	delete pause;
}


bool Game::init()
{
	bool success = true;

	// NOTE: Remove after testing
	state = MENU;

	if (!font.loadFromFile("../content/Fonts/OpenSans-Bold.ttf")) // Replace with a valid font path
	{
		std::cout << "Failed to load font" << std::endl;
		success = false;
	}

	timer_text.setFont(font);
	timer_text.setCharacterSize(20);
	timer_text.setFillColor(sf::Color::White);
	timer_text.setPosition(camera.getPosition().x, camera.getPosition().y);

	if (!level_tileset.loadFromFile("../content/LevelTilemap.png"))
	{
		std::cout << "LevelTilemap.png failed to load" << std::endl;
		success = false;
	}
	if (!character_spritesheet.loadFromFile("../content/CharacterSpritesheet.png"))
	{
		std::cout << "CharacterSpritesheet.png failed to load" << std::endl;
		success = false;
	}
	if (!weapon_spritesheet.loadFromFile("../content/WeaponSpritesheet.png"))
	{
		std::cout << "WeaponSpritesheet.png failed to load" << std::endl;
		success = false;
	}

	// NOTE: Remove after finished testing?
	std::array<std::array<int, 100>, 100> level_tiles;
	for (auto& row : level_tiles)
	{
		row.fill(-1);
	}
	std::array<std::array<int, 50>, 50> temp_tiles;
	// Making temp_tiles for temp level for testing etc etc
	for (auto& row : temp_tiles)
	{
		row.fill(48);
	}
	
	// Make level tiles
	temp_tiles[0] = { 27,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,24 };
	temp_tiles[1] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[2] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[3] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[4] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[5] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[6] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[7] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[8] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[9] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[10] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[11] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[12] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[13] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[14] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[15] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[16] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[17] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[18] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[19] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[20] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[21] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[22] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[23] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[24] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[25] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[26] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[27] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[28] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[29] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[30] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[31] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[32] = { 23,48,48,48,53,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[33] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[34] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[35] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[36] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[37] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[38] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[39] = { 23,48,48,48,48,48,48,48,48,48,52,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[40] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[41] = { 31, 6, 6, 4,48,48,48, 2, 9,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[42] = { 23,48,48,48,48,48,48,48, 1,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[43] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[44] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[45] = { 23,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[46] = { 23,48,48,50,48,48,48,48, 3,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[47] = { 23,48,48,48,48,48,48,48, 5,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[48] = { 23,48,48,48,48,48,48,48, 5,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,21 };
	temp_tiles[49] = { 26,22,22,22,22,22,22,22,30,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,25 };

	//// Fill from pattern
	//for (int i = 0; i < 55; i++)
	//{
	//	temp_tiles[0][i] = Level::Tile::WALL;
	//	temp_tiles[54][i] = Level::Tile::WALL;
	//	temp_tiles[i][0] = Level::Tile::WALL;
	//	temp_tiles[i][54] = Level::Tile::WALL;
	//}
	//
	////x < 2 || x > 4

	//// Horizontal corridors
	//for (int x = 1; x < 55; x++)
	//{
	//	if (x < 10 || x > 27 && x < 42 || x > 46 && x < 50 || x > 52)
	//		temp_tiles[8][x] = Level::Tile::WALL;

	//	if (x < 2 || x > 8 && x < 27)
	//		temp_tiles[15][x] = Level::Tile::WALL;

	//	if (x > 16 && x < 22)
	//		temp_tiles[21][x] = Level::Tile::WALL;

	//	if (x > 48 && x < 50 || x > 52)
	//		temp_tiles[27][x] = Level::Tile::WALL;

	//	if (x > 18 && x < 32 || x > 40)
	//		temp_tiles[34][x] = Level::Tile::WALL;

	//	if (x < 2 || x > 8 && x < 18)
	//		temp_tiles[36][x] = Level::Tile::WALL;

	//	if (x > 18 && x < 23 || x > 29 && x < 44 || x > 50)
	//		temp_tiles[43][x] = Level::Tile::WALL;
	//}

	//for (int y = 1; y < 54; y++)
	//{

	//	if (y < 2 || y > 6 && y < 10 || y > 13 && y < 22 || y > 28 && y < 36)
	//		temp_tiles[y][10] = Level::Tile::WALL;

	//	if (y < 12 || y > 18 && y < 19)
	//		temp_tiles[y][16] = Level::Tile::WALL;

	//	if (y > 20 && y < 44)
	//		temp_tiles[y][18] = Level::Tile::WALL;

	//	if (y > 6 && y < 25)
	//		temp_tiles[y][27] = Level::Tile::WALL;

	//	if (y > 12 && y < 38)
	//		temp_tiles[y][36] = Level::Tile::WALL;

	//	if (y < 2 || y > 6 && y < 28)
	//		temp_tiles[y][48] = Level::Tile::WALL;
	//}

	//// Add spawns and checkpoints
	//temp_tiles[2][2] = Level::Tile::PLAYER_SPAWN;
	//temp_tiles[7][2] = Level::Tile::PLAYER_CHECKPOINT;
	//temp_tiles[10][10] = Level::Tile::ENEMY_SPAWN;
	//temp_tiles[3][12] = Level::Tile::ENEMY_SPAWN;
	//temp_tiles[9][15] = Level::Tile::ENEMY_SPAWN;
	//temp_tiles[25][15] = Level::Tile::ENEMY_SPAWN;

	for (int i = 0; i < temp_tiles.size(); i++)
	{
		for (int j = 0; j < temp_tiles[0].size(); j++)
		{
			level_tiles[i][j] = temp_tiles[i][j];
		}
	}

	level = new Level(level_tileset, character_spritesheet, weapon_spritesheet, level_tiles);
	cutscene = new Cutscene();
	menu = new Menu();
	end  = new End();
	pause = new Pause();
	cutscene->cutsceneInit();
	menu->menuInit(window);
	end->endInit(window);
	pause->pauseInit(window);

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

		if (level->enemy_count <= 0)
		{
			state = END;
		}

		// Temporary timer for testing
		elapsedTime += dt;
		int minutes = static_cast<int>(elapsedTime) / 60;
		int seconds = static_cast<int>(elapsedTime) % 60;
		char buffer[16];
		std::sprintf(buffer, "%02d:%02d", minutes, seconds);
		timer_text.setString(buffer);

		camera.update(level->getPlayer().getSprite().getPosition(), dt);

		// Calculate parameter values for player aiming
		sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition() - window.getPosition());
		sf::FloatRect playercollider = level->getPlayer().getCollider();
		sf::Vector2f relative_position = playercollider.getPosition();
		relative_position += sf::Vector2f(playercollider.getSize().x / 2, playercollider.getSize().y); // NOTE: Do not ask me why y isn't halved I have no idea probably some error somewhere else idfk
		relative_position -= camera.getPosition();
		relative_position.x *= 4;
		relative_position.y *= 4;
		level->getPlayer().rotationTarget(mouse_position, relative_position);
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

	case PAUSE:
		pause->pauseRender(window);
		break;
	}

	//window.draw(timer_text);
	
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
		if (!keydown)
		{
			state = GAMEPLAY;
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

		case sf::Keyboard::Scancode::P:
			state = END; // TODO: Change to PAUSE when pausing implemented
			break;
		}
		break;

	case END:
		if (!keydown)
		{
			state = MENU;
		}

		break;

	case PAUSE:
		
	if(!keydown)
	{
		state = GAMEPLAY;
	}
	break;
	}
}

void Game::mouseInput(const sf::Event& event)
{
	switch (state)
	{
	case GAMEPLAY:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			level->getPlayer().playerInput(Player::Input::ATTACK);
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			level->getPlayer().playerInput(Player::Input::DROP);
		}
		break;
	}

	
}