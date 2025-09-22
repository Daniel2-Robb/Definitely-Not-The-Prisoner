
#include "Level.h"

Level::Level(sf::Texture tileset) : tileset(tileset)
{
	// Initialize all tiles to Empty
	for (auto& row : tiles)
	{
		row.fill(Empty);
	}
	// Set up the tile sprite
	tile_sprite.setTexture(this->tileset);
	tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

Level::Level(sf::Texture tileset, std::array<std::array<Tile, 100>, 100> tiles) : tileset(tileset), tiles(tiles)
{
	// Set up the tile sprite
	tile_sprite.setTexture(this->tileset);
	tile_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}


void Level::update(float dt)
{
	// TODO: Run all Entity object updates and check for collision
}

void Level::render(sf::RenderWindow& window)
{
	// TODO: Render tiles and Entities
}