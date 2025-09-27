
#ifndef _NOTTHEPRISONER_LEVEL_H_
#define _NOTTHEPRISONER_LEVEL_H_

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Objects/Entities/Enemy.h"
#include "../Objects/Entities/Player.h"

class Enemy; // forward declaration


class Level
{
public:
	// NOTE: This may be able to just be private now with the new tile making system
	enum Tile
	{
		EMPTY = -1,
		WALL_NONE,
		WALL_ONE,
		WALL_TWO_STRAIGHT,
		WALL_TWO_CORNER,
		WALL_THREE,
		WALL_FOUR,
		BORDERWALL_OUTCORNER,
		BORDERWALL_STRAIGHT,
		BORDERWALL_INCORNER,
		BORDERWALL_STRAIGHT_CONNECTOR,
		FLOOR_NONE,
		FLOOR_ONE,
		FLOOR_TWO_STRAIGHT,
		FLOOR_TWO_CORNER,
		FLOOR_THREE,
		FLOOR_FOUR,
		FLOOR_DEFAULT,
		FLOOR_LIGHT
	};

private:
	// Rendering/Graphics
	sf::Texture& tileset;
	sf::Texture& character_tileset;
	sf::Sprite tile_sprite;

	// Level Data
	std::array<std::array<Tile, 100>, 100> tiles; // TODO: Change to dynamic memory to cut down on stack size (?)
	std::array<std::array<float, 100>, 100> tile_rotation;

	std::array<std::array<bool, 100>, 100> collision_map;
	std::vector<sf::Vector2f> player_checkpoints; // First entry in this vector is treated as spawn
	std::vector<sf::Vector2f> enemy_spawns;
	int current_checkpoint = 0;
	
	const int tile_size = 16;
	// TODO: Change player checkpoints/spawn from Tile type to GameObject list

	Player* player = nullptr;
	
	std::vector<Entity*> projectiles;

	// TODO: Replace usage in pathfinding with collision_map then remove
	std::vector<std::vector<bool>> walkableGrid;

	// Private methods
	void makeTiles(const std::array<std::array<int, 100>, 100>& map);

	
	bool enemyCollisionCheck(Entity& entity);
	bool bulletCollisionCheck(Entity& entity);

public:
	bool tileCollisionCheck(Entity& entity);

	Level(sf::Texture& tileset, sf::Texture& entity_tileset);
	Level(sf::Texture& tileset, sf::Texture& entity_tileset, const std::array<std::array<int, 100>, 100>& map_tiles);
	~Level();
	std::vector<Enemy*> enemies;
	const std::vector<std::vector<bool>>& getCollisionMap() const { return walkableGrid; }
	void update(float dt);
	void render(sf::RenderWindow& window);

	Player& getPlayer();
	int enemy_count = 0;
};

#endif // _NOTTHEPRISONER_LEVEL_HPP_