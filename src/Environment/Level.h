
#ifndef _NOTTHEPRISONER_LEVEL_H_
#define _NOTTHEPRISONER_LEVEL_H_

#include <array>
#include <SFML/Graphics.hpp>

class Level
{
private:
	enum Tile
	{
		Empty,
		Floor,
		Wall,
		Spawn
	};

	// Rendering/Graphics
	sf::Texture tileset;
	sf::Sprite tile_sprite;

	// Level Data
	std::array<std::array<Tile, 100>, 100> tiles;
	// TODO: Add player (pointer?) and enemy objects

public:
	Level(sf::Texture tileset);
	Level(sf::Texture tileset, std::array<std::array<Tile, 100>, 100> tiles);

	void update(float dt);
	void render(sf::RenderWindow& window);
};

#endif // _NOTTHEPRISONER_LEVEL_HPP_