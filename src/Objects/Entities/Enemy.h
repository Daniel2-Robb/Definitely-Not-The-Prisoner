
#ifndef _NOTTHEPRISONER_ENEMY_H_
#define _NOTTHEPRISONER_ENEMY_H_

#include "Entity.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../Environment/Level.h"
class Level;

// TODO: Add enemy ai logic
class Enemy : public Entity
{
private:
    sf::Vector2f currentDirection;
    float moveTimer = 0.f;

    std::vector<sf::Vector2i> path;
    int currentPathIndex = 0;
    float pathTimer = 0.f;

    bool canSeePlayer(const sf::Vector2f& playerPos, const std::vector<std::vector<bool>>& collisionMap);

public:
    Enemy(sf::Texture& texture);
    void update(float dt, const sf::Vector2f& playerPos, Level& level);
    void updateWithPathfinding(float dt,
        const std::vector<std::vector<bool>>& walkableGrid,
        const sf::Vector2f& playerPos);
};

#endif // _NOTTHEPRISONER_ENEMY_H_