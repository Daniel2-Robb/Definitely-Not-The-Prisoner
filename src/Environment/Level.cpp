
#include "Level.h"

// NOTE: Remove before commit
#include <iostream>

Level::Level(sf::Texture& tileset, sf::Texture& entity_tileset)
	: tileset(tileset), character_tileset(entity_tileset)
{
	// Initialize all tiles to Empty
	for (auto& row : tiles)
	{
		row.fill(Empty);
	}
	// Set up the tile sprite
	tile_sprite.setTexture(this->tileset);
	tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			Tile tile = tiles[i][j];
			collision_map[i][j] = tile == Tile::Wall;
		}
	}

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

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[0].size(); j++)
		{
			Tile tile = tiles[i][j];
			collision_map[i][j] = tile == Tile::Wall;
		}
	}

	player = new Player(this->character_tileset);
	player->getSprite().setTextureRect(sf::IntRect(16, 0, 16, 16));
	player->setCollider(sf::FloatRect(0, 0, 16, 16));
}

Level::~Level()
{
	delete player;
}


bool Level::collisionCheck(Entity& entity)
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
	for (int i = topleft.y; i < downright.y && i < 100 && i > 0; i++)
	{
		for (int j = topleft.x; j < downright.x && j < 100 && j > 0; j++)
		{
			if (collision_map[i][j])
			{
				// NOTE: Remove before commit
				std::cout << j * tile_size << ":" << i * tile_size << std::endl;

				entity.collisonResolve(sf::FloatRect(j * tile_size, i * tile_size, tile_size, tile_size));

				return true;
			}
		}
	}

	return false;
}


void Level::update(float dt)
{
	// Entity updating

	// Entity collision checking
	// TODO: Check for generic Entity collisions
	for (Enemy& enemy : enemies)
	{
		enemy.update(dt);
		collisionCheck(enemy);
	}
	player->update(dt);
	collisionCheck(*player);
}

void Level::render(sf::RenderWindow& window)
{
	// Tile rendering
	for (int y = 0; y < tiles.size(); y++)
	{
		for (int x = 0; x < tiles[0].size(); x++)
		{
			tile_sprite.setPosition(x * tile_size, y * tile_size);

			switch (tiles[y][x])
			{
			case Tile::Floor:
				tile_sprite.setTextureRect(sf::IntRect(48, 16, 16, 16));
				break;

			case Tile::Wall:
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
	for (Enemy& enemy : enemies)
	{
		window.draw(enemy.getSprite());
	}
	window.draw(player->getSprite());
}


Player& Level::getPlayer()
{
	return *player;
}