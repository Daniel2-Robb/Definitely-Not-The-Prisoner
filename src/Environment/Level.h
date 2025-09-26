
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
	
	const int tile_size = 16;
	sf::Vector2f checkpoint_position;
	// TODO: Change player checkpoints/spawn from Tile type to GameObject list

	Player* player = nullptr;
	
	std::vector<Entity*> other_entities;

	// Private methods
	

	std::vector<std::vector<bool>> walkableGrid;

	

public:
	Level(sf::Texture& tileset, sf::Texture& entity_tileset);
	Level(sf::Texture& tileset, sf::Texture& entity_tileset, std::array<std::array<Tile, 100>, 100> tiles);
	~Level();
	std::vector<Enemy*> enemies;
	const std::vector<std::vector<bool>>& getCollisionMap() const { return walkableGrid; }
	void update(float dt);
	void render(sf::RenderWindow& window);

	bool tileCollisionCheck(Entity& entity);
	bool enemyCollisionCheck(Entity& entity);
	bool bulletCollisionCheck(Entity& entity);

	Player& getPlayer();
	int enemy_count = 0;
	

	std::array<std::array<bool, 100>, 100> collision_map;
};

#endif // _NOTTHEPRISONER_LEVEL_HPP_