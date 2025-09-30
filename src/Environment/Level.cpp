
#include "Level.h"

Level::Level(sf::Texture& tileset, sf::Texture& entity_tileset, sf::Texture& weapon_tileset)
	: tileset(tileset), character_tileset(entity_tileset), weapon_tileset(weapon_tileset)
{
	// Initialize all tiles to Empty
	for (auto& row : tiles)
	{
		row.fill(Tile::EMPTY);
	}
	player_checkpoints.push_back(sf::Vector2f(0, 0));

	// Set up the tile sprite
	tile_sprite.setTexture(this->tileset);
	tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	tile_sprite.setOrigin(tile_size * 0.5, tile_size * 0.5);

	for (auto& row : collision_map)
	{
		row.fill(false);
	}

	player = new Player(this->character_tileset, this->weapon_tileset);
	player->getSprite().setTextureRect(sf::IntRect(0, 0, 16, 16));
	player->setCollider(sf::FloatRect(0, 0, 16, 16));
}

Level::Level(sf::Texture& tileset, sf::Texture& character_tileset, sf::Texture& weapon_tileset, const std::array<std::array<int, 100>, 100>& map_tiles)
	: tileset(tileset), character_tileset(character_tileset), weapon_tileset(weapon_tileset)
{
	// Set up the tile sprite
	tile_sprite.setTexture(this->tileset);
	tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	tile_sprite.setOrigin(tile_size * 0.5, tile_size * 0.5);

	// TODO: Run makeTiles() (should make collision_map as well so remove code underneath this)

	// Convert ints to tiles and other logic
	makeTiles(map_tiles);

	for (sf::Vector2f spawns : enemy_spawns)
	{
		Enemy* enemy = new Enemy(this->character_tileset);
		enemy->getSprite().setTextureRect(sf::IntRect(0, 16, 16, 16));
		enemy->setCollider(sf::FloatRect(spawns.x, spawns.y, 16, 16));
		enemies.push_back(enemy);
		enemy_count++;
	}

	player = new Player(this->character_tileset, this->weapon_tileset);
	player->getSprite().setTextureRect(sf::IntRect(0, 0, 16, 16));
	player->setCollider(sf::FloatRect(player_checkpoints[current_checkpoint].x, player_checkpoints[current_checkpoint].y, 16, 16));
}

Level::~Level()
{
	delete player;

	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
}


// Only run once in the constructor to convert int array to tiles and spawns
void Level::makeTiles(const std::array<std::array<int, 100>, 100>& map)
{
	player_checkpoints.push_back(sf::Vector2f(0, 0));

	// All wall values:
	/*
	-1 - empty

	0 - wallnone
	1 - wallone up
	2 - wallone right
	3 - wallone down
	4 - wallone left
	5 - walltwostraight vertical
	6 - walltwostraight horizontal
	7 - walltwocorner upright
	8 - walltwocorner rightdown
	9 - walltwocorner downleft
	10 - walltwocorner leftup
	11 - wallthree notleft
	12 - wallthree notup
	13 - wallthree notright
	14 - wallthree notdown
	15 - wallfour

	16 - borderwalloutcorner upright
	17 - borderwalloutcorner rightdown
	18 - borderwalloutcorner downleft
	19 - borderwalloutcorner leftup
	20 - borderwallstraight facedown
	21 - borderwallstraight faceleft
	22 - borderwallstraight faceup
	23 - borderwallstraight faceright
	24 - borderwallincorner downleft
	25 - borderwallincorner leftup
	26 - borderwallincorner upright
	27 - borderwallincorner rightdown
	28 - borderwallconnector facedown
	29 - borderwallconnector faceleft
	30 - borderwallconnector faceup
	31 - borderwallconnector faceright

	32 - floornone
	33 - floorone up
	34 - floorone right
	35 - floorone down
	36 - floorone left
	37 - floortwostraight vertical
	38 - floortwostraight horizontal
	39 - floortwocorner upright
	40 - floortwocorner rightdown
	41 - floortwocorner downleft
	42 - floortwocorner leftup
	43 - floorthree notleft
	44 - floorthree notup
	45 - floorthree notright
	46 - floorthree notdown
	47 - floorfour
	48 - floordefault
	49 - floorlight

	50 - playerspawn
	51 - playercheckpoint
	52 - enemyspawn

	53 - pistolspawn

	other - empty
	*/

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			// Assign collision_map value to true or false based on the number range
			collision_map[i][j] = (map[i][j] >= 0 && map[i][j] < 32);

			// NOTE: If another soul other than me sees this code, pretend it doesn't exist and isn't real and can't hurt you
			// NOTE: I was tired and didn't want to right slightly nicer but much more complex code alright sue me
			switch (map[i][j])
			{
			case 0:
				tiles[i][j] = Tile::WALL_NONE;
				tile_rotation[i][j] = 0;
				break;
			case 1:
				tiles[i][j] = Tile::WALL_ONE;
				tile_rotation[i][j] = 0;
				break;
			case 2:
				tiles[i][j] = Tile::WALL_ONE;
				tile_rotation[i][j] = 90;
				break;
			case 3:
				tiles[i][j] = Tile::WALL_ONE;
				tile_rotation[i][j] = 180;
				break;
			case 4:
				tiles[i][j] = Tile::WALL_ONE;
				tile_rotation[i][j] = 270;
				break;
			case 5:
				tiles[i][j] = Tile::WALL_TWO_STRAIGHT;
				tile_rotation[i][j] = 0;
				break;
			case 6:
				tiles[i][j] = Tile::WALL_TWO_STRAIGHT;
				tile_rotation[i][j] = 90;
				break;
			case 7:
				tiles[i][j] = Tile::WALL_TWO_CORNER;
				tile_rotation[i][j] = 0;
				break;
			case 8:
				tiles[i][j] = Tile::WALL_TWO_CORNER;
				tile_rotation[i][j] = 90;
				break;
			case 9:
				tiles[i][j] = Tile::WALL_TWO_CORNER;
				tile_rotation[i][j] = 180;
				break;
			case 10:
				tiles[i][j] = Tile::WALL_TWO_CORNER;
				tile_rotation[i][j] = 270;
				break;
			case 11:
				tiles[i][j] = Tile::WALL_THREE;
				tile_rotation[i][j] = 0;
				break;
			case 12:
				tiles[i][j] = Tile::WALL_THREE;
				tile_rotation[i][j] = 90;
				break;
			case 13:
				tiles[i][j] = Tile::WALL_THREE;
				tile_rotation[i][j] = 180;
				break;
			case 14:
				tiles[i][j] = Tile::WALL_THREE;
				tile_rotation[i][j] = 270;
				break;
			case 15:
				tiles[i][j] = Tile::WALL_FOUR;
				tile_rotation[i][j] = 0;
				break;

			case 16:
				tiles[i][j] = Tile::BORDERWALL_OUTCORNER;
				tile_rotation[i][j] = 0;
				break;
			case 17:
				tiles[i][j] = Tile::BORDERWALL_OUTCORNER;
				tile_rotation[i][j] = 90;
				break;
			case 18:
				tiles[i][j] = Tile::BORDERWALL_OUTCORNER;
				tile_rotation[i][j] = 180;
				break;
			case 19:
				tiles[i][j] = Tile::BORDERWALL_OUTCORNER;
				tile_rotation[i][j] = 270;
				break;
			case 20:
				tiles[i][j] = Tile::BORDERWALL_STRAIGHT;
				tile_rotation[i][j] = 0;
				break;
			case 21:
				tiles[i][j] = Tile::BORDERWALL_STRAIGHT;
				tile_rotation[i][j] = 90;
				break;
			case 22:
				tiles[i][j] = Tile::BORDERWALL_STRAIGHT;
				tile_rotation[i][j] = 180;
				break;
			case 23:
				tiles[i][j] = Tile::BORDERWALL_STRAIGHT;
				tile_rotation[i][j] = 270;
				break;
			case 24:
				tiles[i][j] = Tile::BORDERWALL_INCORNER;
				tile_rotation[i][j] = 0;
				break;
			case 25:
				tiles[i][j] = Tile::BORDERWALL_INCORNER;
				tile_rotation[i][j] = 90;
				break;
			case 26:
				tiles[i][j] = Tile::BORDERWALL_INCORNER;
				tile_rotation[i][j] = 180;
				break;
			case 27:
				tiles[i][j] = Tile::BORDERWALL_INCORNER;
				tile_rotation[i][j] = 270;
				break;
			case 28:
				tiles[i][j] = Tile::BORDERWALL_STRAIGHT_CONNECTOR;
				tile_rotation[i][j] = 0;
				break;
			case 29:
				tiles[i][j] = Tile::BORDERWALL_STRAIGHT_CONNECTOR;
				tile_rotation[i][j] = 90;
				break;
			case 30:
				tiles[i][j] = Tile::BORDERWALL_STRAIGHT_CONNECTOR;
				tile_rotation[i][j] = 180;
				break;
			case 31:
				tiles[i][j] = Tile::BORDERWALL_STRAIGHT_CONNECTOR;
				tile_rotation[i][j] = 270;
				break;

			case 32:
				tiles[i][j] = Tile::FLOOR_NONE;
				tile_rotation[i][j] = 0;
				break;
			case 33:
				tiles[i][j] = Tile::FLOOR_ONE;
				tile_rotation[i][j] = 0;
				break;
			case 34:
				tiles[i][j] = Tile::FLOOR_ONE;
				tile_rotation[i][j] = 90;
				break;
			case 35:
				tiles[i][j] = Tile::FLOOR_ONE;
				tile_rotation[i][j] = 180;
				break;
			case 36:
				tiles[i][j] = Tile::FLOOR_ONE;
				tile_rotation[i][j] = 270;
				break;
			case 37:
				tiles[i][j] = Tile::FLOOR_TWO_STRAIGHT;
				tile_rotation[i][j] = 0;
				break;
			case 38:
				tiles[i][j] = Tile::FLOOR_TWO_STRAIGHT;
				tile_rotation[i][j] = 90;
				break;
			case 39:
				tiles[i][j] = Tile::FLOOR_TWO_CORNER;
				tile_rotation[i][j] = 0;
				break;
			case 40:
				tiles[i][j] = Tile::FLOOR_TWO_CORNER;
				tile_rotation[i][j] = 90;
				break;
			case 41:
				tiles[i][j] = Tile::FLOOR_TWO_CORNER;
				tile_rotation[i][j] = 180;
				break;
			case 42:
				tiles[i][j] = Tile::FLOOR_TWO_CORNER;
				tile_rotation[i][j] = 270;
				break;
			case 43:
				tiles[i][j] = Tile::FLOOR_THREE;
				tile_rotation[i][j] = 0;
				break;
			case 44:
				tiles[i][j] = Tile::FLOOR_THREE;
				tile_rotation[i][j] = 90;
				break;
			case 45:
				tiles[i][j] = Tile::FLOOR_THREE;
				tile_rotation[i][j] = 180;
				break;
			case 46:
				tiles[i][j] = Tile::FLOOR_THREE;
				tile_rotation[i][j] = 270;
				break;
			case 47:
				tiles[i][j] = Tile::FLOOR_FOUR;
				tile_rotation[i][j] = 0;
				break;
			case 48:
				tiles[i][j] = Tile::FLOOR_DEFAULT;
				tile_rotation[i][j] = 0;
				break;
			case 49:
				tiles[i][j] = Tile::FLOOR_LIGHT;
				tile_rotation[i][j] = 0;
				break;

			case 50:
				tiles[i][j] = Tile::FLOOR_LIGHT;
				tile_rotation[i][j] = 0;
				player_checkpoints.at(0) = sf::Vector2f(j * tile_size, i * tile_size);
				break;
			case 51:
				tiles[i][j] = Tile::FLOOR_LIGHT;
				tile_rotation[i][j] = 0;
				player_checkpoints.push_back(sf::Vector2f(j * tile_size, i * tile_size));
				break;
			case 52:
				tiles[i][j] = Tile::FLOOR_DEFAULT;
				tile_rotation[i][j] = 0;
				enemy_spawns.push_back(sf::Vector2f(j * tile_size, i * tile_size));
				break;

				// Weapon spawn tiles
			case 53:
			{
				tiles[i][j] = Tile::FLOOR_DEFAULT;
				tile_rotation[i][j] = 0;
				Weapon weapon = Weapon(weapon_tileset, Weapon::Type::PISTOL);
				weapon.setCollider(sf::FloatRect(j * tile_size, i * tile_size, 16, 16));
				weapons.push_back(weapon);
				break;
			}

			default:
				tiles[i][j] = Tile::EMPTY;
				tile_rotation[i][j] = 0;
				break;
			}
		}
	}
}


bool Level::tileCollisionCheck(Entity& entity)
{
	// Convert entity position and size to int and 'stretch' to all tiles it would intersect
	sf::Vector2i topleft(entity.getCollider().getPosition().x, entity.getCollider().getPosition().y);
	sf::Vector2i downright = topleft;
	topleft.x /= tile_size;
	topleft.y /= tile_size;

	downright += sf::Vector2i(entity.getCollider().getSize().x, entity.getCollider().getSize().y);
	downright.x += downright.x % tile_size == 0 ? 0 : tile_size;
	downright.y += downright.y % tile_size == 0 ? 0 : tile_size;
	downright.x /= tile_size;
	downright.y /= tile_size;

	// Check all intersecting tiles for collidable types
	for (int i = topleft.y; i < downright.y && i < 100 && i >= 0; i++)
	{
		for (int j = topleft.x; j < downright.x && j < 100 && j >= 0; j++)
		{
			if (collision_map[i][j])
			{
				entity.collisonResolve(sf::FloatRect(j * tile_size, i * tile_size, tile_size, tile_size));

				return true;
			}
		}
	}

	return false;
}

bool Level::enemyCollisionCheck(Entity& entity)
{
	for (Enemy* enemy : enemies)
	{
		if (enemy->is_loaded && 
			enemy != &entity &&
			enemy->getCollider().intersects(entity.getCollider()))
		{
			entity.collisonResolve(enemy->getCollider());
			return true;
		}
	}

	return false;
}

bool Level::bulletCollisionCheck(Entity& entity)
{
	for (Entity* bullet : player->weapon->getProjectiles())
	{
		if (bullet->is_loaded &&
			bullet->getCollider().intersects(entity.getCollider()))
		{
			bullet->is_loaded = false;

			return true;
		}
	}

	return false;
}


void Level::update(float dt)
{
	// Entity updating and collision checking
	player->update(dt);
	while (tileCollisionCheck(*player));

	for (Enemy* enemy : enemies)
	{
		if (enemy->is_loaded)
		{
			enemy->update(dt, player->getSprite().getPosition(), *this);
			// Check for collision with level geometry
			while (tileCollisionCheck(*enemy));
			// Check for collision with other enemies
			while (enemyCollisionCheck(*enemy));
			// Check for collision between bullet Entities and Enemies
			if (bulletCollisionCheck(*enemy))
			{
				enemy->is_loaded = false;
				enemy_count--;
			}
		}
	}

	// Check for collision between Player and Enemies
	if (enemyCollisionCheck(*player))
	{
		// TODO: Make corpse at death location
		// TODO: Remove life and reset player position

		player->player_life++;
		sf::FloatRect temprect = player->getCollider();
		temprect.left = player_checkpoints[current_checkpoint].x;
		temprect.top = player_checkpoints[current_checkpoint].y;
		player->setCollider(temprect);
	}

	// Check for projectile collision with enemies
	for (Entity* projectile : player->weapon->getProjectiles())
	{
		if (tileCollisionCheck(*projectile))
		{
			projectile->is_loaded = false;
		}
	}

	// Check for player collision with items
	for (Weapon& weapon : weapons)
	{
		if (weapon.is_loaded && 
			player->weapon != nullptr &&
			weapon.getCollider().intersects(player->getCollider()))
		{
			for (Entity* projectile : player->weapon->getProjectiles())
			{
				projectile->is_loaded = false;
			}

			weapon.is_loaded = false;
			player->weapon = &weapon;
		}
	}
}

// TODO: Cut down on draw calls as it's quite expensive and the primary performance inhibitor(?)
void Level::render(sf::RenderWindow& window)
{
	// Tile rendering
	for (int y = 0; y < tiles.size(); y++)
	{
		for (int x = 0; x < tiles[0].size(); x++)
		{
			Tile& tile = tiles[y][x];
			if (tile != Tile::EMPTY)
			{
				tile_sprite.setPosition((x + 0.5) * tile_size, (y + 0.5) * tile_size);

				// TODO: Add texturerect for other tile types
				if (tile >= 0 && tile < 6)
				{
					tile_sprite.setTextureRect({ 16 * tile, 0, 16, 16 });
				}
				else if (tile >= 6 && tile < 10)
				{
					tile_sprite.setTextureRect({ 16 * (tile - 6), 16, 16, 16 });
				}
				else if (tile >= 10 && tile < 16)
				{
					tile_sprite.setTextureRect({ 16 * (tile - 10), 32, 16, 16 });
				}
				else if (tile >= 16 && tile < 18)
				{
					tile_sprite.setTextureRect({ 16 * (tile - 16), 48, 16, 16 });
				}
				tile_sprite.setRotation(tile_rotation[y][x]);

				/*switch (tiles[y][x])
				{
				case Tile::FLOOR_DEFAULT:
					tile_sprite.setTextureRect(sf::IntRect(0, 48, 16, 16));
					break;

				case Tile::WALL:
					tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
					break;

				default:
					tile_sprite.setTextureRect(sf::IntRect(0, 64, 16, 16));
					break;
				}*/

				window.draw(tile_sprite);
			}
		}
	}

	// Render objects
	for (Weapon& weapon : weapons)
	{
		if (weapon.is_loaded)
		{
			window.draw(weapon.getSprite());
		}
	}

	// Render entities
	for (Enemy* enemy : enemies)
	{
		if (enemy->is_loaded)
		{
			window.draw(enemy->getSprite());
		}
	}

	window.draw(player->getSprite());

	// Draw projectiles
	for (Entity* projectile : player->weapon->getProjectiles())
	{
		if (projectile->is_loaded)
		{
			window.draw(projectile->getSprite());
		}
	}
}


Player& Level::getPlayer()
{
	return *player;
}

