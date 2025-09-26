
#include "Level.h"

Level::Level(sf::Texture& tileset, sf::Texture& entity_tileset)
	: tileset(tileset), character_tileset(entity_tileset)
{
	// Initialize all tiles to Empty
	for (auto& row : tiles)
	{
		row.fill(Tile::EMPTY);
	}
	tiles[0][0] = Tile::PLAYER_SPAWN;

	// Set up the tile sprite
	tile_sprite.setTexture(this->tileset);
	tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			Tile tile = tiles[i][j];
			collision_map[i][j] = tile == Tile::WALL;
		}
	}

	checkpoint_position = sf::Vector2f(0, 0);

	player = new Player(this->character_tileset);
	player->getSprite().setTextureRect(sf::IntRect(16, 0, 16, 16));
	player->setCollider(sf::FloatRect(0, 0, 16, 16));
}

Level::Level(sf::Texture& tileset, sf::Texture& character_tileset, std::array<std::array<Tile, 100>, 100> tiles)
	: tileset(tileset), character_tileset(character_tileset), tiles(tiles)
{
	// Set up the tile sprite
	tile_sprite.setTexture(this->tileset);
	tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	// Making collision_map
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			Tile tile = tiles[i][j];
			collision_map[i][j] = (tile == Tile::WALL);

			// Finding player start position
			if (tile == Tile::PLAYER_SPAWN)
			{
				checkpoint_position.x = j * tile_size;
				checkpoint_position.y = i * tile_size;
			}
			if (tile == Tile::ENEMY_SPAWN)
			{
				Enemy* enemy = new Enemy(this->character_tileset);
				enemy->getSprite().setTextureRect(sf::IntRect(0, 0, 16, 16));
				enemy->setCollider(sf::FloatRect(j * tile_size, i * tile_size, 16, 16));
				enemy->getSprite().setPosition(j * tile_size, i * tile_size);
				enemies.push_back(enemy);
				enemy_count++;

			}
		}
	}

	player = new Player(this->character_tileset);
	player->getSprite().setTextureRect(sf::IntRect(16, 0, 16, 16));
	player->setCollider(sf::FloatRect(checkpoint_position.x, checkpoint_position.y, 16, 16));
}

Level::~Level()
{
	delete player;

	for (Enemy* enemy : enemies)
	{
		delete enemy;
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
	for (Entity* bullet : other_entities)
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
		temprect.left = checkpoint_position.x;
		temprect.top = checkpoint_position.y;
		player->setCollider(temprect);
	}
}

void Level::render(sf::RenderWindow& window)
{
	// Tile rendering
	for (int y = 0; y < tiles.size(); y++)
	{
		for (int x = 0; x < tiles[0].size(); x++)
		{
			tile_sprite.setPosition(x * tile_size, y * tile_size);

			// TODO: Add texturerect for other tile types
			switch (tiles[y][x])
			{
			case Tile::FLOOR_DEFAULT:
				tile_sprite.setTextureRect(sf::IntRect(48, 16, 16, 16));
				break;

			case Tile::WALL:
				tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				break;

			default:
				tile_sprite.setTextureRect(sf::IntRect(32, 16, 16, 16));
				break;
			}

			window.draw(tile_sprite);
		}
	}

	// TODO: Render entities
	for (Enemy* enemy : enemies)
	{
		if (enemy->is_loaded)
		{
			window.draw(enemy->getSprite());
		}
	}

	window.draw(player->getSprite());
}


Player& Level::getPlayer()
{
	return *player;
}

