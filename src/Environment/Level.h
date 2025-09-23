
#ifndef _NOTTHEPRISONER_LEVEL_H_
#define _NOTTHEPRISONER_LEVEL_H_

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Entities/Enemy.h"
#include "../Entities/Player.h"

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
	std::array<std::array<Tile, 100>, 100> tiles; // TODO: Change to dynamic memory to cut down on stack size (?)
	Player* player = nullptr;
	std::vector<Enemy> enemies;
	std::vector<GameObject*> objects;

public:
	Level(sf::Texture tileset);
	Level(sf::Texture tileset, std::array<std::array<Tile, 100>, 100> tiles);

	void update(float dt);
	void render(sf::RenderWindow& window);

	Player& getPlayer();
};

#endif // _NOTTHEPRISONER_LEVEL_HPP_