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

bool Enemy::canSeePlayer(const sf::Vector2f& playerPos, const std::vector<std::vector<bool>>& collisionMap)
{
    sf::Vector2f start(collider.left + collider.width / 2, collider.top + collider.height / 2);
    sf::Vector2f dir = playerPos - start;
    float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    const float visionRadius = 120.f;
    if (distance > visionRadius) return false;

    dir /= distance; // normalize
    sf::Vector2f current = start;
    const float step = 4.f;
    for (float i = 0; i < distance; i += step)
    {
        current += dir * step;
        int tileX = static_cast<int>(current.x) / 16;
        int tileY = static_cast<int>(current.y) / 16;
        if (tileX < 0 || tileY < 0 || tileY >= collisionMap.size() || tileX >= collisionMap[0].size())
            break;
        if (collisionMap[tileY][tileX]) return false; // wall blocks vision
    }
    return true;
}

void Enemy::update(float dt, const sf::Vector2f& playerPos, Level& level)
{
    // --- Line-of-sight check ---
    bool seesPlayer = canSeePlayer(playerPos, level.getCollisionMap());

    sf::Vector2f toPlayer = playerPos - sf::Vector2f(collider.left, collider.top);
    float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

    const float visionRadius = 120.f;
    const float stopDistance = 20.f;

    // --- Decide movement ---
    if (seesPlayer && distance > stopDistance && distance < visionRadius)
    {
        // Chase player
        sf::Vector2f dir = toPlayer / distance;
        velocity = dir * speed;
    }
    else if (seesPlayer && distance <= stopDistance)
    {
        // Stop when close
        velocity = { 0.f, 0.f };
    }
    else
    {
        // Wandering logic
        moveTimer -= dt;
        if (moveTimer <= 0.f)
        {
            float chance = static_cast<float>(std::rand()) / RAND_MAX;
            if (chance < 0.2f)
                currentDirection = { 0.f, 0.f }; // random stop
            else
            {
                float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.14159265f;
                currentDirection = { std::cos(angle), std::sin(angle) };
            }

            velocity = currentDirection * speed;
            moveTimer = 2.f + static_cast<float>(std::rand() % 200) / 100.f; // 2–4s
        }
    }

    // --- Predict collision ---
    sf::FloatRect nextCollider = collider;
    nextCollider.left += velocity.x * dt;
    nextCollider.top += velocity.y * dt;

    // Use Level collision check
    Entity tempEntity = *this;
    tempEntity.setCollider(nextCollider);
    if (level.collisionCheck(tempEntity))
    {
        // Collision detected: pick new direction
        if (seesPlayer)
        {
            // Try to move towards player but pick a slightly different angle
            float angleToPlayer = std::atan2(toPlayer.y, toPlayer.x);
            float offset = ((std::rand() % 2 == 0) ? 0.25f : -0.25f); // radians
            float newAngle = angleToPlayer + offset;
            currentDirection = { std::cos(newAngle), std::sin(newAngle) };
        }
        else
        {
            // Wandering: random new direction
            float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.14159265f;
            currentDirection = { std::cos(angle), std::sin(angle) };
        }
        velocity = currentDirection * speed;

        // Stop briefly to avoid jitter
        if (!seesPlayer) velocity = { 0.f, 0.f };
        moveTimer = 0.5f;
    }

    // --- Apply movement ---
    Entity::update(dt);
}
