
#include "Level.h"

Level::Level(sf::Texture& tileset, sf::Texture& entity_tileset)
	: tileset(tileset), entity_tileset(entity_tileset)
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

	player = new Player(this->entity_tileset);
}

Level::Level(sf::Texture& tileset, sf::Texture& entity_tileset, std::array<std::array<Tile, 100>, 100> tiles)
	: tileset(tileset), entity_tileset(entity_tileset), tiles(tiles)
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

	player = new Player(this->entity_tileset);
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
	downright.x /= tile_size;
	downright.y /= tile_size;
	downright += sf::Vector2i(1, 1);

	// Check all intersecting tiles for collidable types
	for (int i = topleft.y; i <= downright.y && i < 100; i++)
	{
		for (int j = topleft.x; j <= downright.x && j < 100; j++)
		{
			if (collision_map[i][j])
			{
				entity.collisonResolve(sf::FloatRect(j, i, tile_size, tile_size));

				return true;
			}
		}
	}

	return false;
}


void Level::update(float dt)
{
	// Object and Entity collision checking
	// TODO: Check for generic Entity collisions

	for (Enemy& enemy : enemies)
	{
		sf::Vector2i topleft(enemy.getCollider().getPosition().x, enemy.getCollider().getPosition().y);
		sf::Vector2i downright = topleft;
		topleft.x /= tile_size;
		topleft.y /= tile_size;

		downright += sf::Vector2i(enemy.getCollider().getSize().x, enemy.getCollider().getSize().y);
		downright.x /= tile_size;
		downright.y /= tile_size;
		downright += sf::Vector2i(1, 1);

		for (int i = topleft.y; i <= downright.y && i < 100; i++)
		{
			for (int j = topleft.x; j <= downright.x && j < 100; j++)
			{
				if (collision_map[i][j])
				{

				}
			}
		}
	}
}

void Level::render(sf::RenderWindow& window)
{
	// TODO: Render tiles and Entities
}


Player& Level::getPlayer()
{
	return *player;
}