#include "Enemy.h"
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(sf::Texture& texture) : Entity(texture)
{
    speed = 50.f; // slower than player
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Start moving in a random 2D direction
    float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.14159265f;
    currentDirection = { std::cos(angle), std::sin(angle) };
    velocity = currentDirection * speed;
    moveTimer = 2.f; // 2 seconds before changing direction
}



void Enemy::update(float dt, const sf::Vector2f& playerPos, const std::vector<std::vector<bool>>& walkableGrid)
{
    // Distance to player
    sf::Vector2f toPlayer = playerPos - sf::Vector2f(collider.left, collider.top);
    float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

    const float visionRadius = 120.f; // enemy sees player within 120 pixels

    if (distance < visionRadius)
    {
        // Chase player
        sf::Vector2f dir = toPlayer;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0.01f)
        {
            dir /= len; // normalize
            velocity = dir * speed;
        }
        else
        {
            velocity = { 0.f, 0.f };
        }

        moveTimer = 0.f; // reset wander timer
    }
    else
    {
        // --- wandering logic ---
        moveTimer -= dt;

        if (moveTimer <= 0.f)
        {
            float chance = static_cast<float>(std::rand()) / RAND_MAX;

            if (chance < 0.2f) // 20% chance to stop
                currentDirection = { 0.f, 0.f };
            else
            {
                float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.14159265f;
                currentDirection = { std::cos(angle), std::sin(angle) };
            }

            velocity = currentDirection * speed;
            moveTimer = 2.f + static_cast<float>(std::rand() % 200) / 100.f; // 2–4s
        }
    }

    // --- collision avoidance with walls ---
    sf::FloatRect nextCollider = collider;
    nextCollider.left += velocity.x * dt;
    nextCollider.top += velocity.y * dt;

    int tileSize = 16;
    int leftTile = static_cast<int>(nextCollider.left / tileSize);
    int rightTile = static_cast<int>((nextCollider.left + nextCollider.width) / tileSize);
    int topTile = static_cast<int>(nextCollider.top / tileSize);
    int bottomTile = static_cast<int>((nextCollider.top + nextCollider.height) / tileSize);

    bool hitWall = false;
    for (int y = topTile; y <= bottomTile && y < walkableGrid.size(); ++y)
    {
        for (int x = leftTile; x <= rightTile && x < walkableGrid[0].size(); ++x)
        {
            if (x < 0 || y < 0) continue;
            if (!walkableGrid[y][x])
            {
                hitWall = true;
                break;
            }
        }
        if (hitWall) break;
    }

    if (hitWall)
    {
        // Pick a new random direction when hitting a wall
        float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.14159265f;
        currentDirection = { std::cos(angle), std::sin(angle) };
        velocity = currentDirection * speed;
        moveTimer = 1.f; // shorter time until next change
    }

    // Move enemy
    Entity::update(dt);
}








