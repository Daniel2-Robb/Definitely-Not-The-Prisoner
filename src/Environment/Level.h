
#ifndef _NOTTHEPRISONER_LEVEL_H_
#define _NOTTHEPRISONER_LEVEL_H_

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Objects/Entities/Enemy.h"
#include "../Objects/Entities/Player.h"

class Level
{
public:
	enum Tile
	{
		EMPTY,
		FLOOR_DEFAULT,
		FLOOR_LIGHT,
		WALL,
		PLAYER_SPAWN,
		PLAYER_CHECKPOINT,
		ENEMY_SPAWN
	};

private:
	// Rendering/Graphics
	sf::Texture& tileset;
	sf::Texture& character_tileset;
	sf::Sprite tile_sprite;

	// Level Data
	std::array<std::array<Tile, 100>, 100> tiles; // TODO: Change to dynamic memory to cut down on stack size (?)
	std::array<std::array<bool, 100>, 100> collision_map;
	const int tile_size = 16;
	sf::Vector2f checkpoint_position;

	Player* player = nullptr;
	std::vector<Enemy> enemies;
	std::vector<Entity*> other_entities;

	// Private methods
	bool collisionCheck(Entity& entity);

	std::vector<std::vector<bool>> walkableGrid;


public:
	Level(sf::Texture& tileset, sf::Texture& entity_tileset);
	Level(sf::Texture& tileset, sf::Texture& entity_tileset, std::array<std::array<Tile, 100>, 100> tiles);
	~Level();

	void update(float dt);
	void render(sf::RenderWindow& window);

	Player& getPlayer();
};

#endif // _NOTTHEPRISONER_LEVEL_HPP_